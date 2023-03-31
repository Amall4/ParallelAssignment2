#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>

#define NUM_THREADS 4

int M, N, K;
double **A, **B, **C;

void *matrix_multiply(void *arg) {
    int tid = *(int*) arg;
    int start = tid * M / NUM_THREADS;
    int end = (tid + 1) * M / NUM_THREADS;
    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    M = atoi(argv[1]);
    N = atoi(argv[2]);
    K = atoi(argv[3]);

    A = (double **) malloc(M * sizeof(double *));
    for (int i = 0; i < M; i++) {
        A[i] = (double *) malloc(K * sizeof(double));
    }

    B = (double **) malloc(K * sizeof(double *));
    for (int i = 0; i < K; i++) {
        B[i] = (double *) malloc(N * sizeof(double));
    }

    C = (double **) malloc(M * sizeof(double *));
    for (int i = 0; i < M; i++) {
        C[i] = (double *) malloc(N * sizeof(double));
    }

    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int rc;

    srand(time(NULL));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            A[i][j] = (double) rand() / RAND_MAX;
        }
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = (double) rand() / RAND_MAX;
        }
    }

    double start_time = omp_get_wtime();

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        rc = pthread_create(&threads[i], NULL, matrix_multiply, (void*) &thread_args[i]);
        if (rc) {
            printf("Error: return code from pthread_create() is %d\n", rc);
            exit(1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            printf("Error: return code from pthread_join() is %d\n", rc);
            exit(1);
        }
    }

    double end_time = omp_get_wtime();
    double computation_time = (end_time - start_time);
    double execution_time = (double) (omp_get_wtime() - start_time);
    printf("Computation time: %f ms\n", computation_time);
    printf("Execution time: %f ms\n ",execution_time);

    return 0;
}