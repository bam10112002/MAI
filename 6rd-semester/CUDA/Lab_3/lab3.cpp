#include <iostream>
#include <cmath>
#include <iostream>

using namespace std;

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

// Нахождение обратной матрицы, результат записывается в переменную А
void inversion(double** A, int N) {
    double temp;
    double **E = new double *[N];

    for (int i = 0; i < N; i++)
        E[i] = new double [N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            E[i][j] = 0.0;
            if (i == j)
                E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++) {
        temp = A[k][k];
        for (int j = 0; j < N; j++) {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++) {
            temp = A[i][k];
            for (int j = 0; j < N; j++) {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--) {
        for (int i = k - 1; i >= 0; i--) {
            temp = A[i][k];
            for (int j = 0; j < N; j++) {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = E[i][j];

    for (int i = 0; i < N; i++)
        delete [] E[i];

    delete [] E;
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



struct pixel {
    unsigned char x;
    unsigned char y;
    unsigned char z;
    unsigned char a;
} typedef pixel;

void pixelToMatrix(pixel p, double ** res) {
//    double** res = init();
    res[0][0] = p.x;
    res[1][0] = p.y;
    res[2][0] = p.z;
}

// Функция получения класса
int argmax(const double* arr, int numOfClasses) {
    int max_index = 0;
    double max_value = arr[0];
    for (int i = 1; i < numOfClasses; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
            max_index = i;
        }
    }
    return max_index;
}

int main() {
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
    auto* image = (pixel*)malloc(sizeof(pixel) * width * height);
    fread(image, sizeof(pixel), width * height, fp);
    fclose(fp);

    auto avgMatrix = (double***)malloc(sizeof(double**) * n);
    auto covMatrix = (double***)malloc(sizeof(double**) * n);
    for (int i = 0; i < n; i++) {
        //AVG
        avgMatrix[i] = (double**)malloc(sizeof(double*) * 3);
        for (int j = 0; j < 3; j++) {
          avgMatrix[i][j] = (double*)malloc(sizeof(double) * 3);
        }

        double xSum = 0;
        double ySum = 0;
        double zSum = 0;
        for (int j = 0; j < lens[i] * 2; j += 2) {
          pixel pix = image[data[i][j + 1] * width + data[i][j]];
          xSum += pix.x;
          ySum += pix.y;
          zSum += pix.z;
        }
        avgMatrix[i][0][0] = xSum * 1.0/lens[i];
        avgMatrix[i][1][0] = ySum * 1.0/lens[i];
        avgMatrix[i][2][0] = zSum * 1.0/lens[i];

        // Ковариация
        covMatrix[i] = init();
        auto cov = init();
        auto left = init();
        auto right = init();
        double** transposed = init();
        for (int j = 0; j < lens[i] * 2; j += 2) {
            pixel pix = image[data[i][j + 1] * width + data[i][j]];
            pixelToMatrix(pix, left);
            pixelToMatrix(pix, right);
            difference(left, avgMatrix[i]);
            difference(right, avgMatrix[i]);
            transpose(right, transposed);
            mult(left,3,1,transposed,1,3, cov);
            sum(covMatrix[i], cov);
        }
        free(transposed);
        free(left);
        free(right);
        free(cov);

        for(int c=0; c<3; c++)
            for(int v=0; v<3; v++)
                covMatrix[i][c][v] /= lens[i]-1;
        inversion(covMatrix[i], 3);
    }

    // Скопировать на Device avg, cov, image

    // Ядро
    auto classes = (double*)malloc(n*sizeof(double));
    auto pix1 = init();
    auto pix2 = init();
    double **transposed = init();
    for (int i = 0; i < width*height; i++) {
        int pixNum = i;
        for (int cls = 0; cls < n; cls++) {
            pixelToMatrix(image[pixNum], pix1);
            pixelToMatrix(image[pixNum], pix2);

            difference(pix1, avgMatrix[cls]);
            transpose(pix1, transposed);
            for (int c = 0; c < 3; c++)
                for (int v = 0; v < 3; v++)
                    transposed[c][v] *= -1.0;

            mult(transposed, 1, 3, covMatrix[cls], 3, 3, pix1);
            difference(pix2, avgMatrix[cls]);
            mult(pix1, 1, 3, pix2, 3, 1, transposed);
            classes[cls] = transposed[0][0];
          }
          image[pixNum].a = argmax(classes, n);
    }

    for (int i = 0; i < 3; i++) {
        free(transposed[i]);
        free(pix1[i]);
        free(pix2[i]);
    }
    free(transposed);
    free(pix1);
    free(pix2);
    free(classes);
    // Конец ядра


    fp = fopen(fileOut, "wb");
    fwrite(image,sizeof(pixel), width * height, fp);
    fclose(fp);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            free(avgMatrix[i][j]);
            free(covMatrix[i][j]);
        }
        free(avgMatrix[i]);
        free(covMatrix[i]);
    }
    free(avgMatrix);
    free(covMatrix);

    return 0;
}

