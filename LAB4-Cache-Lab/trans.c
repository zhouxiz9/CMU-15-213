/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include "cachelab.h"

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

void trans_32(int M, int N, int A[N][M], int B[M][N]);
void trans_61(int M, int N, int A[N][M], int B[M][N]);
void trans_64(int M, int N, int A[N][M], int B[M][N]);
int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32) {
        trans_32(M, N, A, B);
    } else if (M == 61 && N == 67) {
        trans_61(M, N, A, B);
    } else if (M == 64 && N == 64) {
        trans_64(M, N, A, B);
    }
}

char trans_32_desc[] = "Transpose 32 submission";
void trans_32(int M, int N, int A[N][M], int B[M][N])
{  
    int ii, jj, i, j, tmp, prev; // 6 variables
    for (ii = 0; ii < 32; ii += 8) {
        for (jj = 0; jj < 32; jj += 8) {

            for (i = ii; i < ii + 8; i++) {
                for (j = jj; j < jj + 8; j++) {
                    tmp = A[i][j];
                    if (i == j) {
                        if (i > 0) {
                            B[j - 1][i - 1] = prev;
                        }
                        prev = tmp;
                    } else {
                        B[j][i] = tmp;
                    }
                }
            }
            B[jj + 7][ii + 7] = A[ii + 7][jj + 7];
        }
    }
}


char trans_61_desc[] = "Transpose 61 submission";
void trans_61(int M, int N, int A[N][M], int B[M][N])
{
    int ii, jj, i, j, tmp, prev; // 6 variables

    for (jj = 0; jj < 56; jj += 8) {
        for (ii = 0; ii < 64; ii += 8) {

             for (i = ii; i < ii + 8; i++) {
                for (j = jj; j < jj + 8; j++) {
                    tmp = A[i][j];
                    if (i == j) {
                        if (i > 0) {
                            B[j - 1][i - 1] = prev;
                        }
                        prev = tmp;
                    } else {
                        B[j][i] = tmp;
                    }
                }
            }
            B[jj + 7][ii + 7] = A[ii + 7][jj + 7];
        }
    }

    for (jj = 0; jj < 56; jj += 8) {
        for (ii = 64; ii < 67; ii++) {
            for (j = jj; j < jj + 8; j++) {
                B[j][ii] = A[ii][j];
            }
        }
    }

    for (ii = 0; ii < 64; ii += 8) {
        for (jj = 56; jj < 61; jj++) {
            for (i = ii; i < ii + 8; i++) {
                B[jj][i] = A[i][jj];
            }
        }
    }
   

    for (ii = 64; ii < 67; ii++) {
        for (jj = 56; jj < 61; jj++) {
            B[jj][ii] = A[ii][jj];
        }
    }
}

void helper2(int ii, int jj, int A[64][64], int B[64][64]) {
    int i, n0, n1, n2, n3, n4, n5; // 7 variables

    n0 = A[ii][jj + 1];
    n1 = A[ii][jj + 2];
    n2 = A[ii][jj + 3];
    n3 = A[ii + 1][jj + 2];
    n4 = A[ii + 1][jj + 3];
    n5 = A[ii + 2][jj + 3];

    for (i = ii; i < ii + 4; i++) {
        B[jj][i] = A[i][jj];
    }

    for (i = ii + 1; i < ii + 4; i++) {
        B[jj + 1][i] = A[i][jj + 1];
    }

    for (i = ii + 2; i < ii + 4; i++) {
        B[jj + 2][i] = A[i][jj + 2];
    }

    B[jj + 3][ii + 3] = A[ii + 3][jj + 3];

    B[jj + 1][ii] = n0;
    B[jj + 2][ii] = n1;
    B[jj + 3][ii] = n2;
    B[jj + 2][ii + 1] = n3;
    B[jj + 3][ii + 1] = n4;
    B[jj + 3][ii + 2] = n5;
}


char trans_64_desc[] = "Transpose 64 submission";
void trans_64(int M, int N, int A[N][M], int B[M][N])
{
    // 12 variables
    int ii, jj, i, j, n0, n1, n2, n3, n4, n5, n6, n7;

    for (ii = 0; ii < 64; ii += 8) {
        for (jj = 0; jj < 64; jj += 8) {
            if (ii == jj) {
                helper2(ii, jj, A, B);
                helper2(ii, jj + 4, A, B);
                helper2(ii + 4, jj, A, B);
                helper2(ii + 4, jj + 4, A, B);
            } else {
                for (i = ii; i < ii + 4; i++) {
                    for (j = jj; j < jj + 4; j++) {
                        B[j][i] = A[i][j];
                    }
                }

                n0 = A[ii][jj + 4];
                n1 = A[ii][jj + 5];
                n2 = A[ii][jj + 6];
                n3 = A[ii][jj + 7];
                n4 = A[ii + 1][jj + 4];
                n5 = A[ii + 1][jj + 5];
                n6 = A[ii + 1][jj + 6];
                n7 = A[ii + 1][jj + 7];

                for (i = ii + 4; i < ii + 8; i++) {
                    for (j = jj; j < jj + 4; j++) {
                        B[j][i] = A[i][j];
                    }
                }

                for (i = ii + 4; i < ii + 8; i++) {
                    for (j = jj + 4; j < jj + 8; j++) {
                        B[j][i] = A[i][j];
                    }
                }

                for (i = ii + 2; i < ii + 4; i++) {
                    for (j = jj + 4; j < jj + 8; j++) {
                        B[j][i] = A[i][j];
                    }
                }

                B[jj + 4][ii] = n0;
                B[jj + 5][ii] = n1;
                B[jj + 6][ii] = n2;
                B[jj + 7][ii] = n3;

                B[jj + 4][ii + 1] = n4;
                B[jj + 5][ii + 1] = n5;
                B[jj + 6][ii + 1] = n6;
                B[jj + 7][ii + 1] = n7;
            }
        }
    }
}


/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    
}


/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    // registerTransFunction(trans, trans_desc); 
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

