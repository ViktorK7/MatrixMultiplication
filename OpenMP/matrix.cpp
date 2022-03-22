#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <omp.h>

void ParallelMatrixCalculation(double* A, double* B, double* C, const long size) // C = A*B
{
    int i, j, k;
#pragma omp parallel for private(i,j,k)
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++) {
            C[i * size + j] = 0.0;
            for (k = 0; k < size; k++)
                C[i * size + j] += A[i * size + k] * B[k * size + j];
        }
}

void PrintMatrix(double* A, const long size)
{
    for (long i = 0; i < size; i++) {
        for (long j = 0; j < size; j++)
            printf("%f ", A[i * size + j]);
        printf("\n");
    }
}

void Test()
{
    const long size = 200;

    double A[size][size];
    double B[size][size];
    double C[size][size];

    for (long i = 0; i < size; i++)
    {
        for (long j = 0; j < size; j++)
        {
            A[i][j] = rand();
            B[i][j] = rand();

        }
    }

    clock_t time = clock();
    ParallelMatrixCalculation((double*)&A, (double*)&B, (double*)&C, size);
    time = clock() - time;
    double time_taken = ((double)time) / CLOCKS_PER_SEC;
    printf("Parallel execute \n", time_taken);


    PrintMatrix((double*)&C, size);
}

int main(int argc, char* argv[])
{


        if (argc == 1) {
            Test();
        }
        else {
            long size = atol(argv[1]);
            printf("size=%ld\n", size);
            double* A = new double[size * size];
            double* B = new double[size * size];
            double* C = new double[size * size];
            ParallelMatrixCalculation(A, B, C, size);
            PrintMatrix(C, size);
            delete[] C;
            delete[] B;
            delete[] A;
        }

}