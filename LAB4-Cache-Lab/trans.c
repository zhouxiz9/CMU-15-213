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

    for (int ii = 0; ii < 32; ii += 8) {
        for (int jj = 0; jj < 32; jj += 8) {

            int n0, n1, n2, n3, n4, n5, n6, n7;

            for (int i = ii; i < ii + 8; i++) {
                for (int j = jj; j < jj + 8; j++) {
                    if (i == j) {
                        if (i % 8 == 0) {
                            n0 = A[i][j];
                        } else if (i % 8 == 1) {
                            n1 = A[i][j];
                        } else if (i % 8 == 2) {
                            n2 = A[i][j];
                        } else if (i % 8 == 3) {
                            n3 = A[i][j];
                        } else if (i % 8 == 4) {
                            n4 = A[i][j];
                        } else if (i % 8 == 5) {
                            n5 = A[i][j];
                        } else if (i % 8 == 6) {
                            n6 = A[i][j];
                        } else if (i % 8 == 7) {
                            n7 = A[i][j];
                        }
                    } else {
                        B[j][i] = A[i][j];
                    }
                }
            }

            for (int i = ii; i < ii + 8; i++) {
                for (int j = jj; j < jj + 8; j++) {
                    if (i == j) {
                        if (j % 8 == 0) {
                            B[j][i] = n0;
                        } else if (j % 8 == 1) {
                            B[j][i] = n1;
                        } else if (j % 8 == 2) {
                            B[j][i] = n2;
                        } else if (j % 8 == 3) {
                            B[j][i] = n3;
                        } else if (j % 8 == 4) {
                            B[j][i] = n4;
                        } else if (j % 8 == 5) {
                            B[j][i] = n5;
                        } else if (j % 8 == 6) {
                            B[j][i] = n6;
                        } else if (j % 8 == 7) {
                            B[j][i] = n7;
                        }
                    }
                }
            }
        }
    }
}


char trans_61_desc[] = "Transpose 61 submission";
void trans_61(int M, int N, int A[N][M], int B[M][N])
{
    int n0, n1, n2, n3, n4, n5, n6, n7;

    for (int jj = 0; jj < 56; jj += 8) {
        for (int ii = 0; ii < 64; ii += 8) {

            for (int i = ii; i < ii + 8; i++) {
                for (int j = jj; j < jj + 8; j++) {
                    if (i == j) {
                        if (i % 8 == 0) {
                            n0 = A[i][j];
                        } else if (i % 8 == 1) {
                            n1 = A[i][j];
                        } else if (i % 8 == 2) {
                            n2 = A[i][j];
                        } else if (i % 8 == 3) {
                            n3 = A[i][j];
                        } else if (i % 8 == 4) {
                            n4 = A[i][j];
                        } else if (i % 8 == 5) {
                            n5 = A[i][j];
                        } else if (i % 8 == 6) {
                            n6 = A[i][j];
                        } else if (i % 8 == 7) {
                            n7 = A[i][j];
                        }
                    } else {
                        B[j][i] = A[i][j];
                    }
                }
            }  

            for (int i = ii; i < ii + 8; i++) {
                for (int j = jj; j < jj + 8; j++) {
                    if (i == j) {
                        if (j % 8 == 0) {
                            B[j][i] = n0;
                        } else if (j % 8 == 1) {
                            B[j][i] = n1;
                        } else if (j % 8 == 2) {
                            B[j][i] = n2;
                        } else if (j % 8 == 3) {
                            B[j][i] = n3;
                        } else if (j % 8 == 4) {
                            B[j][i] = n4;
                        } else if (j % 8 == 5) {
                            B[j][i] = n5;
                        } else if (j % 8 == 6) {
                            B[j][i] = n6;
                        } else if (j % 8 == 7) {
                            B[j][i] = n7;
                        }
                    }
                }
            }
        }
    }

    for (int jj = 0; jj < 56; jj += 8) {
        for (int ii = 64; ii < 67; ii++) {
            for (int j = jj; j < jj + 8; j++) {
                B[j][ii] = A[ii][j];
            }
        }
    }

    for (int ii = 0; ii < 64; ii += 8) {
        for (int jj = 56; jj < 61; jj++) {
            for (int i = ii; i < ii + 8; i++) {
                B[jj][i] = A[i][jj];
            }
        }
    }
   

    for (int ii = 64; ii < 67; ii++) {
        for (int jj = 56; jj < 61; jj++) {
            B[jj][ii] = A[ii][jj];
        }
    }
}

char trans_64_desc[] = "Transpose 64 submission";
void trans_64(int M, int N, int A[N][M], int B[M][N])
{
    for (int ii = 0; ii < 64; ii += 4) {
        for (int jj = 0; jj < 64; jj += 4) {

            int n0, n1, n2, n3;
            // int n4, n5, n6, n7;

            for (int i = ii; i < ii + 4; i++) {
                for (int j = jj; j < jj + 4; j++) {
                    if (abs(i - j) % 4 == 0) {
                        if (i % 4 == 0) {
                            n0 = A[i][j];
                        } else if (i % 4 == 1) {
                            n1 = A[i][j];
                        } else if (i % 4 == 2) {
                            n2 = A[i][j];
                        } else if (i % 4 == 3) {
                            n3 = A[i][j];
                        }
                    } else {
                        B[j][i] = A[i][j];
                    }
                }
            }

            for (int i = ii; i < ii + 4; i++) {
                for (int j = jj; j < jj + 4; j++) {
                    if (abs(i - j) % 4 == 0) {
                        if (i % 4 == 0) {
                            B[j][i] = n0;
                        } else if (i % 4 == 1) {
                            B[j][i] = n1;
                        } else if (i % 4 == 2) {
                            B[j][i] = n2;
                        } else if (i % 4 == 3) {
                            B[j][i] = n3;
                        }
                    }
                }
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
    registerTransFunction(trans, trans_desc); 
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

