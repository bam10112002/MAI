#include <stdio.h>
#include <float.h>

class COV_AVG {
private:
    double3 avg;
    double * cov_matr;
    double * cov_matr_GPU;

public: __host__ COV_AVG(uchar4 * pixels, int numPixels) {
    initAVG(pixels, numPixels);
    initCOV(pixels, numPixels);

    cudaMalloc( & cov_matr_GPU, sizeof(double) * 9);
    cudaMemcpy(cov_matr_GPU, cov_matr, sizeof(double) * 9, cudaMemcpyHostToDevice);
  }

  void initAVG(uchar4 * pixels, int numPixels){
      avg = make_double3(0., 0., 0.);

      for (int i = 0; i < numPixels; i++) {
          avg.x += pixels[i].x;
          avg.y += pixels[i].y;
          avg.z += pixels[i].z;
      }
      avg.x /= numPixels;
      avg.y /= numPixels;
      avg.z /= numPixels;
  }

  void initCOV(uchar4 * pixels, int numPixels) {
      cov_matr = (double * ) malloc(sizeof(double) * 9);
      double3 tmp;
      for (int i = 0; i < numPixels; i++) {
          auto pix = pixels[i];
          tmp = make_double3(pix.x - avg.x, pix.y - avg.y, pix.z - avg.z);
          cov_matr[0] += tmp.x * tmp.x;
          cov_matr[1] += tmp.x * tmp.y;
          cov_matr[2] += tmp.x * tmp.z;
          cov_matr[3] += tmp.y * tmp.x;
          cov_matr[4] += tmp.y * tmp.y;
          cov_matr[5] += tmp.y * tmp.z;
          cov_matr[6] += tmp.z * tmp.x;
          cov_matr[7] += tmp.z * tmp.y;
          cov_matr[8] += tmp.z * tmp.z;
      }

      for (int i = 0; i < 9; i++)
          cov_matr[i] /= (numPixels - 1);
      inverseCOV();
  }

    void inverseCOV() {
        double * tmp = (double * ) malloc(sizeof(double) * 9);

        tmp[0] =   cov_matr[4] * cov_matr[8] - cov_matr[5] * cov_matr[7];
        tmp[1] = -(cov_matr[1] * cov_matr[8] - cov_matr[2] * cov_matr[7]);
        tmp[2] =   cov_matr[1] * cov_matr[5] - cov_matr[2] * cov_matr[4];
        tmp[3] = -(cov_matr[3] * cov_matr[8] - cov_matr[5] * cov_matr[6]);
        tmp[4] =   cov_matr[0] * cov_matr[8] - cov_matr[2] * cov_matr[6];
        tmp[5] = -(cov_matr[0] * cov_matr[5] - cov_matr[2] * cov_matr[3]);
        tmp[6] =   cov_matr[3] * cov_matr[7] - cov_matr[4] * cov_matr[6];
        tmp[7] = -(cov_matr[0] * cov_matr[7] - cov_matr[1] * cov_matr[6]);
        tmp[8] =   cov_matr[0] * cov_matr[4] - cov_matr[1] * cov_matr[3];

        double det = (cov_matr[0] * cov_matr[4] * cov_matr[8]) +
                     (cov_matr[1] * cov_matr[5] * cov_matr[6]) +
                     (cov_matr[2] * cov_matr[3] * cov_matr[7]) -
                     (cov_matr[2] * cov_matr[4] * cov_matr[6]) -
                     (cov_matr[1] * cov_matr[3] * cov_matr[8]) -
                     (cov_matr[0] * cov_matr[5] * cov_matr[7]);

        for (int i = 0; i < 9; i++)
            tmp[i] /= det;
        memcpy(cov_matr, tmp, 9 * sizeof(double));
        free(tmp);
    }


    __device__ double3 getAVG() {
    return avg;
  }

  __device__ double* getCOV() {
    return cov_matr_GPU;
  }

  __host__ ~COV_AVG() {
    free(cov_matr);
  }
};

__global__ void kernel(uchar4 * input_pixels, int len, COV_AVG * cov_avg, int num_classes) {

  int idx = threadIdx.x + blockIdx.x * blockDim.x;
  int offset = gridDim.x * blockDim.x;

  for (;idx < len; idx += offset) {
        uchar4 pixel = input_pixels[idx];
        double val = DBL_MAX - 1;
        int class_ind = 0;

        for (int i = 0; i < num_classes; i++) {
            auto avg = cov_avg[i].getAVG();
            auto cov = cov_avg[i].getCOV();
            auto tmp = make_double3(pixel.x - avg.x, pixel.y - avg.y, pixel.z - avg.z);

          double res =  (tmp.x * cov[0] + tmp.y * cov[3] + tmp.z * cov[6]) * tmp.x +
                        (tmp.x * cov[1] + tmp.y * cov[4] + tmp.z * cov[7]) * tmp.y +
                        (tmp.x * cov[2] + tmp.y * cov[5] + tmp.z * cov[8]) * tmp.z;

          if (res < val) {
              val = res;
            class_ind = i;
          }
        }

        input_pixels[idx].w = class_ind;
  }
}

int main() {
    // Считывание данных
    char fileIn[1024];
    char fileOut[1024];
    scanf("%s", fileIn);
    scanf("%s", fileOut);

    int width, height;
    FILE * fp = fopen(fileIn, "rb");
    fread( & width, sizeof(int), 1, fp);
    fread( & height, sizeof(int), 1, fp);

    uchar4* image_bin = (uchar4*) malloc(sizeof(uchar4) * width * height);
    fread(image_bin, sizeof(uchar4), width * height, fp);
    fclose(fp);

    int count_classes;
    scanf("%d", &count_classes);

    COV_AVG*  matrixes = (COV_AVG*) malloc(sizeof(COV_AVG) * count_classes);
    for (int i = 0; i < count_classes; i++) {
        int pixel_count;
        scanf("%d", &pixel_count);

        uchar4* class_data = (uchar4*) malloc(sizeof(uchar4) * pixel_count);
        int x_pos, y_pos;

        for (int j = 0; j < pixel_count; j++) {
            scanf("%d", &x_pos);
            scanf("%d", &y_pos);
            class_data[j] = image_bin[y_pos * width + x_pos];
        }

        matrixes[i] = COV_AVG(class_data, pixel_count);
        free(class_data);
    }

    // Копирование данных на GPU
    uchar4 * image_dev;
    COV_AVG * dev_matrixes;

    cudaMalloc( & image_dev, sizeof(uchar4) * width * height);
    cudaMemcpy(image_dev, image_bin, sizeof(uchar4) * width * height, cudaMemcpyHostToDevice);

    cudaMalloc( & dev_matrixes, sizeof(COV_AVG) * count_classes);
    cudaMemcpy(dev_matrixes, matrixes, sizeof(COV_AVG) * count_classes, cudaMemcpyHostToDevice);

    kernel <<< 32, 32 >>> (image_dev, width * height, dev_matrixes, count_classes);

    cudaMemcpy(image_bin, image_dev, sizeof(uchar4) * width * height, cudaMemcpyDeviceToHost);


    cudaFree(image_dev);
    cudaFree(dev_matrixes);
    free(matrixes);

    // запись всех данных в файл
    fp = fopen(fileOut, "wb");
    fwrite( & width, sizeof(int), 1, fp);
    fwrite( & height, sizeof(int), 1, fp);
    fwrite(image_bin, sizeof(uchar4), width * height, fp);
    fclose(fp);

    free(image_bin);
    return 0;
}