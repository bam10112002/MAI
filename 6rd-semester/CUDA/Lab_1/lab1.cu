%%cu
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

__global__ void pow(double *arr, int n) {
  int idx = threadIdx.x + blockIdx.x * blockDim.x;
  int offset = gridDim.x * blockDim.x;

  while (idx < n) {
    arr[idx] *= arr[idx];
    idx += offset;
  }
}

int main() {
  double *arr;
  double *arr_dev;
  int n = 0;

  scanf("%d", &n);
  double* arr = (double*)malloc(n*sizeof(double));
  for (int i = 0; i < n; i++) {
    scanf("%lf", &arr[i]);
    //arr[i] = i;
  }


  cudaMalloc(&arr_dev, sizeof(double)*n);
  cudaMemcpy(arr_dev, arr, sizeof(double)*n, cudaMemcpyHostToDevice);

  pow<<<1024, 1024>>>(arr_dev, n);

  cudaMemcpy(arr, arr_dev, sizeof(double) * n, cudaMemcpyDeviceToHost);

  for (int i = 0; i < n; i++) {
    printf("%e ", arr[i]);
  }
  printf("\n");

  cudaFree(arr_dev);
  free(arr);

  return 0;
}