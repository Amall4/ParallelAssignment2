#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4000
#define K 700
#define M 5000

int main() {
  int i, j, k;
  double sum;
  double elapsed_time;
  clock_t start_time, end_time;

  double** A = (double**)malloc(N * sizeof(double*));
  double** B = (double**)malloc(M * sizeof(double*));
  double** C = (double**)malloc(K * sizeof(double*));
  for (i = 0; i < N; i++) {
    A[i] = (double*)malloc(N * sizeof(double));
    B[i] = (double*)malloc(M * sizeof(double));
    C[i] = (double*)malloc(K * sizeof(double));
  }

  for (i = 0; i < N; i++) {
    for (j = 0; j < K; j++) {
      A[i][j] = (double)rand() / (double)RAND_MAX;
    }
  }
   for (i = 0; i < K; i++) {
    for (j = 0; j < M; j++) {
         B[i][j] = (double)rand() / (double)RAND_MAX;
    }
   }
  start_time = clock();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      int mult = 0;
      for (k = 0; k < K; k++) {
        mult += A[i][k] * B[k][j];
      }
      C[i][j] = mult;
    }
  }
  end_time = clock();
  elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

  printf("Elapsed time: %.3f seconds\n", elapsed_time);
  return 0;
}
