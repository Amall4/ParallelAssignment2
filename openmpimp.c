#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <M> <N> <K>\n", argv[0]);
        return 1;
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int K = atoi(argv[3]);

    if (M <= 0 || N <= 0 || K <= 0) {
        printf("Error: Matrix dimensions must be positive integers\n");
        return 1;
    }

    double *A = (double*) malloc(M * K * sizeof(double));
    double *B = (double*) malloc(K * N * sizeof(double));
    double *C = (double*) malloc(M * N * sizeof(double));

    // Initialize matrices with random values
    for (int i = 0; i < M*K; i++) {
        A[i] = (double) rand() / RAND_MAX;
    }
    for (int i = 0; i < K*N; i++) {
        B[i] = (double) rand() / RAND_MAX;
    }
    for (int i = 0; i < M*N; i++) {
        C[i] = 0.0;
    }

    int num_threads = omp_get_max_threads();
    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < K; k++) {
                sum += A[i*K + k] * B[k*N + j];
            }
            C[i*N + j] = sum;
        }
    }

    // Print the results
    printf("Matrix A:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            printf("%f ", A[i*K + j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix B:\n");
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", B[i*N + j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix C = A * B:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", C[i*N + j]);
        }
        printf("\n");
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}
