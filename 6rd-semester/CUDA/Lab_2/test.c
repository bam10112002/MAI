#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  char* inFileName = (char*)malloc(1024);
  char* outFileName = (char*)malloc(1024);
  scanf("%s", inFileName);
  scanf("%s", outFileName);

//  int w, h;
//  FILE *fp = fopen("myfile.dat", "rb");
//  fread(&w, sizeof(int), 1, fp);
//  fread(&h, sizeof(int), 1, fp);
//  uchar4 *data = (uchar4 *)malloc(sizeof(uchar4) * w * h);
//  fread(data, sizeof(uchar4), w * h, fp);
//  fclose(fp);



//  fp = fopen("out.data", "wb");
//  fwrite(&w, sizeof(int), 1, fp);
//  fwrite(&h, sizeof(int), 1, fp);
//  fwrite(data, sizeof(uchar4), w * h, fp);
//  fclose(fp);
//
//  free(data);
  free(inFileName);
  free(outFileName);
  return 0;
}
