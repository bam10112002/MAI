#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <float.h>

class Matrix {
public:
    int n = 3;
    double* arr;
    double* arr_dev;
    Matrix() {
        arr = (double*)malloc(sizeof(double) * n * n);
        cudaMalloc(&arr_dev, sizeof(double)  * n * n);
    }
//    ~Matrix() {
//        free(arr);
//        cudaFree(arr_dev);
//    }
    void del() {
        free(arr);
        cudaFree(arr_dev);
    }

    double get(int row, int column) {
        return arr[row * n + column];
    }
    __device__ double get_dev(int row, int column) {
        return arr_dev[row * n + column];
    }

    void set(int row, int column, double data) {
        arr[row * n + column] = data;
    }

    void toGPU() {
        cudaMemcpy(arr_dev, arr, sizeof(double)*9, cudaMemcpyHostToDevice);
    }

    void toCPU() {
        cudaMemcpy(arr, arr_dev, sizeof(double) * 9, cudaMemcpyDeviceToHost);
    }

    void inverse() {
        double det = (arr[0] * arr[4] * arr[8]) +
                     (arr[1] * arr[5] * arr[6]) +
                     (arr[2] * arr[3] * arr[7]) -
                     (arr[2] * arr[4] * arr[6]) -
                     (arr[1] * arr[3] * arr[8]) -
                     (arr[0] * arr[5] * arr[7]);

        double * temp_matrix = (double * ) malloc(sizeof(double) * 9);

        temp_matrix[0] =   arr[4] * arr[8] - arr[5] * arr[7];
        temp_matrix[1] = -(arr[1] * arr[8] - arr[2] * arr[7]);
        temp_matrix[2] =   arr[1] * arr[5] - arr[2] * arr[4];
        temp_matrix[3] = -(arr[3] * arr[8] - arr[5] * arr[6]);
        temp_matrix[4] =   arr[0] * arr[8] - arr[2] * arr[6];
        temp_matrix[5] = -(arr[0] * arr[5] - arr[2] * arr[3]);
        temp_matrix[6] =   arr[3] * arr[7] - arr[4] * arr[6];
        temp_matrix[7] = -(arr[0] * arr[7] - arr[1] * arr[6]);
        temp_matrix[8] =   arr[0] * arr[4] - arr[1] * arr[3];

        for (int i = 0; i < 9; i++) {
            temp_matrix[i] /= det;
        }

        memcpy(arr, temp_matrix, 9 * sizeof(double));
        free(temp_matrix);
    }
};

struct pixel {
    unsigned char x;
    unsigned char y;
    unsigned char z;
    unsigned char a;
} typedef pixel;

// Перемножение двух матриц
void mult(double** a, int r1, int c1, double** b, int r2, int c2, double** res) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
    }
}

// Перемножение двух векторов
void multVectors(double* a, double*b, double** c) {
    for (int i = 0; i < 3; i ++) {
        for (int j = 0 ; j < 3; j++) {
            c[i][j] = a[i] * b[j];
        }
    }
}

// Вывод матрицы в консоль
void printMatrix(double** a) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%lf\t", a[i][j]);
        }
        printf("\n");
    }
}

void pixelToMatrix(pixel p, double ** res) {
//    double** res = init();
    res[0][0] = p.x;
    res[1][0] = p.y;
    res[2][0] = p.z;
}

// Транспонируем
void transpose(double** a, double** res) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            res[j][i]=a[i][j];
}

// инициализирует пустую матрицу
double** init(){
    double** arr = (double**)malloc(sizeof(double*)*3);
    for(int i = 0; i < 3; i++){
        arr[i] = (double*)malloc(sizeof(double)*3);
    }
    return arr;
}

// Записывает резульат в а
void difference(double** a, double** b) {
    for(int i=0;i<3;i++)// Транспонируем
        for(int j=0;j<3;j++)
            a[i][j] -= b[i][j];
}

// Записывает резульат в а
void sum(double** a, double** b) {
    for(int i=0; i<3; i++)// Транспонируем
        for(int j=0; j<3; j++)
            a[i][j] += b[i][j];
}

__global__
void mahalanobis_distance(pixel* image_data, Matrix* avg, Matrix* cov, int pix_len, int num_classes) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    int offset = gridDim.x * blockDim.x;

    for (;idx < pix_len; idx += offset) {
        pixel pix = image_data[idx];
        int maxInd = 0;
        auto maxVal = (-1) * DBL_MAX;
        for (int i = 0; i < num_classes; i++) {
            double a = pix.x - avg[i].get_dev(0,0);
            double b = pix.y - avg[i].get_dev(1,0);
            double c = pix.z - avg[i].get_dev(2,0);

            double res = (-a*cov[i].get_dev(0,0) - b*cov[i].get_dev(1,0)-c*cov[i].get_dev(2,0)) * a +
                         (-a*cov[i].get_dev(0,1) - b*cov[i].get_dev(1,1)-c*cov[i].get_dev(2,1)) * b +
                         (-a*cov[i].get_dev(0,2) - b*cov[i].get_dev(1,2)-c*cov[i].get_dev(2,2)) * c;

            if (res > maxVal) {
                maxInd = i;
                maxVal = res;
            }
        }
        int a = maxInd;
        image_data[idx].a = a;
    }
}
int main() {

    // Считывание данных
    char fileIn[1024];
    char fileOut[1024];
    scanf("%s", fileIn);
    scanf("%s", fileOut);

    int** data;
    int n;
    scanf("%d", &n);
    data = (int**)malloc(sizeof(int*)*n);
    int* lens = (int*)malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++) {
        scanf("%d", lens + i);
        data[i] = (int*)malloc(sizeof(int)*lens[i]*2);
        for (int j = 0; j < lens[i]*2; j++) {
            scanf("%d", data[i]+j);
        }
    }

    FILE* fp = fopen(fileIn, "rb");
    if (!fp) perror("fopen");
    int width;
    int height;

    fread(&width, sizeof(int), 1, fp);
    fread(&height, sizeof(int), 1, fp);
    auto image = (pixel*)malloc(sizeof(pixel) * width * height);
    fread(image, sizeof(pixel), width * height, fp);
    fclose(fp);

    auto avgList = (Matrix*)malloc(sizeof(Matrix) * n);
    auto covList = (Matrix*)malloc(sizeof(Matrix) * n);

    for (int i = 0; i < n; i++) {
        //AVG
        double xSum = 0;
        double ySum = 0;
        double zSum = 0;
        for (int j = 0; j < lens[i] * 2; j += 2) {
            pixel pix = image[data[i][j + 1] * width + data[i][j]];
            xSum += pix.x;
            ySum += pix.y;
            zSum += pix.z;
        }
        avgList[i] = Matrix();
        avgList[i].set(0,0, xSum * 1.0/lens[i]);
        avgList[i].set(1,0, ySum * 1.0/lens[i]);
        avgList[i].set(2,0, zSum * 1.0/lens[i]);

        avgList[i].toGPU();

        // Ковариация
        auto cov = init();
        auto left = init();
        auto right = init();
        double** transposed = init();
        covList[i] = Matrix();
        for (int j = 0; j < lens[i] * 2; j += 2) {
            pixel pix = image[data[i][j + 1] * width + data[i][j]];
            pixelToMatrix(pix, left);
            pixelToMatrix(pix, right);
            left[0][0] -= avgList[i].get(0,0);
            left[1][0] -= avgList[i].get(1,0);
            left[2][0] -= avgList[i].get(2,0);

            right[0][0] -= avgList[i].get(0,0);
            right[1][0] -= avgList[i].get(1,0);
            right[2][0] -= avgList[i].get(2,0);

            transpose(right, transposed);
            mult(left,3,1,transposed,1,3, cov);

            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    covList[i].set(r,c, covList[i].get(r,c) + cov[r][c]);
                }
            }
        }

        free(transposed);
        free(left);
        free(right);
        free(cov);

        for(int c=0; c<3; c++)
            for(int v=0; v<3; v++)
                covList[i].set(c,v, covList[i].get(c,v) / (lens[i]-1));

        covList[i].inverse();
        covList[i].toGPU();
    }
    Matrix* covList_dev;
    cudaMalloc(&covList_dev, sizeof(Matrix)  * n);
    cudaMemcpy(covList_dev, covList, sizeof(Matrix) * n, cudaMemcpyHostToDevice);

    Matrix* avgList_dev;
    cudaMalloc(&avgList_dev, sizeof(Matrix)  * n);
    cudaMemcpy(avgList_dev, avgList, sizeof(Matrix) * n, cudaMemcpyHostToDevice);

    pixel * img_dev;
    cudaMalloc(&img_dev, sizeof(pixel)  * width*height);
    cudaMemcpy(img_dev, image, sizeof(pixel)  * width*height, cudaMemcpyHostToDevice);

    mahalanobis_distance <<< 32, 32 >>> (img_dev, avgList_dev, covList_dev, width*height, n);

    cudaMemcpy(image, img_dev, sizeof(pixel)  * width*height, cudaMemcpyDeviceToHost);

    fp = fopen(fileOut, "wb");
    fwrite(&width , sizeof(int), 1, fp);
    fwrite(&height, sizeof(int), 1, fp);
    fwrite(image,sizeof(pixel), width * height, fp);
    fclose(fp);

    cudaFree(covList_dev);
    cudaFree(avgList_dev);
    cudaFree(img_dev);
    for (int i = 0; i < n; i++) {
        free(data[i]);
        covList[i].del();
        avgList[i].del();
    }
    free(image);
    free(avgList);
    free(covList);
    free(lens);

    free(data);


    return 0;
}