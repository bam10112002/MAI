#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CSC(call)  									\
do {											\
	cudaError_t res = call;							\
	if (res != cudaSuccess) {							\
		fprintf(stderr, "ERROR in %s:%d. Message: %s\n",			\
				__FILE__, __LINE__, cudaGetErrorString(res));		\
		exit(0);								\
	}										\
} while(0)


texture<uchar4, 2, cudaReadModeElementType> tex;
const double red = 0.299;
const double green = 0.587;
const double blue = 0.114;


__global__ void roberts(uchar4 *out, int w, int h) {
  int idx = blockDim.x * blockIdx.x + threadIdx.x;
  int idy = blockDim.y * blockIdx.y + threadIdx.y;
  int offsetx = blockDim.x * gridDim.x;
  int offsety = blockDim.y * gridDim.y;
  int x, y;
  uchar4 p,p1,p2,p3;
  for(y = idy; y < h; y += offsety)
    for(x = idx; x < w; x += offsetx) {
      p  = tex2D(tex, x+1, y+1);
      p1 = tex2D(tex, x,   y);
      p2 = tex2D(tex, x+1, y);
      p3 = tex2D(tex, x,   y+1);

      double Y  = red * p.x  + green * p.y  + blue * p.z;
      double Y1 = red * p1.x + green * p1.y + blue * p1.z;
      double Y2 = red * p2.x + green * p2.y + blue * p2.z;
      double Y3 = red * p3.x + green * p3.y + blue * p3.z;
      double Yres = sqrt((Y-Y1)*(Y-Y1) + (Y2-Y3)*(Y2-Y3));
      if (Yres > 255)
        Yres = 255;

      out[y * w + x] = make_uchar4(Yres, Yres, Yres, p.w);
    }
}
// Y = 0.299 R+ 0.587*G + 0.144*B

int main() {
  char* inFileName = (char*)malloc(1024);
  char* outFileName = (char*)malloc(1024);
  scanf("%s", inFileName);
  scanf("%s", outFileName);

  int w, h;
  FILE *fp = fopen(inFileName, "rb");
  fread(&w, sizeof(int), 1, fp);
  fread(&h, sizeof(int), 1, fp);
  uchar4 *data = (uchar4 *)malloc(sizeof(uchar4) * w * h);
  fread(data, sizeof(uchar4), w * h, fp);
  fclose(fp);

  cudaArray *arr;
  cudaChannelFormatDesc ch = cudaCreateChannelDesc<uchar4>();
  CSC(cudaMallocArray(&arr, &ch, w, h));

  CSC(cudaMemcpy2DToArray(arr, 0, 0, data, w * sizeof(uchar4), w * sizeof(uchar4), h, cudaMemcpyHostToDevice));

  tex.normalized = false;
  tex.filterMode = cudaFilterModePoint;
  tex.channelDesc = ch;
  tex.addressMode[0] = cudaAddressModeClamp;
  tex.addressMode[1] = cudaAddressModeClamp;

  CSC(cudaBindTextureToArray(tex, arr, ch));

  uchar4 *dev_out;
  CSC(cudaMalloc(&dev_out, sizeof(uchar4) * w * h));

  roberts<<< dim3(16, 16), dim3(32, 32) >>>(dev_out, w, h);
  CSC(cudaGetLastError());

  CSC(cudaMemcpy(data, dev_out, sizeof(uchar4) * w * h, cudaMemcpyDeviceToHost));
  CSC(cudaUnbindTexture(tex));
  CSC(cudaFreeArray(arr));
  CSC(cudaFree(dev_out));

  fp = fopen(outFileName, "wb");
  fwrite(&w, sizeof(int), 1, fp);
  fwrite(&h, sizeof(int), 1, fp);
  fwrite(data, sizeof(uchar4), w * h, fp);
  fclose(fp);

  free(data);
  free(inFileName);
  free(outFileName);
  return 0;
}
