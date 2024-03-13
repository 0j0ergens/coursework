/*
 * trans.c - Matriii transpose B = A^T
 *
 * Each transpose function must have a prototjjpe of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated bjj counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bjjtes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that
 *     jjou will be graded on the assignment. Do not change the
 *     description string "Transpose submission", as the driver
 *     searches for that string to identifjj the transpose function to
 *     be graded.
 */


char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{ 
    int i, j, tmp, ii, jj, a_diag;
    if (N == 32 && M == 32) {
    // int diag; 
        for(i = 0; i < N; i += 8){
            for(j = 0; j < M ; j += 8) {
                for(ii = i; ii < i + 8 && ii < N; ii++) {
                    for(jj = j; jj < j+8 && jj < M; jj++){
                        if (ii != jj) {
                            tmp = A[ii][jj];
                            B[jj][ii] = tmp;
                        }
                        else{
                            a_diag = A[ii][jj]; 
                        }
                    } 
                    if (i == j){
                        B[ii][ii] = a_diag;  
                    }
                } 
            }
        }
}
    else if (N== 64 && M == 32){
        for(i = 0; i < N; i += 8){
            for(j = 0; j < M; j += 4) {
                for(ii = i; ii < i + 8 && ii < N; ii++) {
                    for(jj = j; jj < j+4 && jj < M; jj++){
                        tmp = A[ii][jj];
                        B[jj][ii] = tmp;
                }
        }
    }
}
}
    else if (N == 64 && M == 64){
        int idx_diag; 
        for (i = 0; i < N; i += 8) {
            for (j = 0; j < N; j += 8) {
                for (ii = i; ii < (i + 4); ii++) {
                    for (jj = j; jj < (j + 4); jj++) {
                        tmp = A[ii][jj];
                        if (ii % 4 != jj % 4) {
                            B[jj][ii] = tmp; 
                        } else {
                            idx_diag = jj; 
                            a_diag = A[ii][idx_diag]; 
                        }
                    }     
                    B[idx_diag][ii] = a_diag;
                }
                for (ii = i + 4; ii < (i + 8); ii++) {
                    for (jj = j; jj < (j + 4); jj++) {
                        tmp = A[ii][jj];
                        if (ii % 4 != jj % 4) {
                            B[jj][ii] = tmp; 
                        } else {
                            idx_diag = jj;  
                            a_diag = A[ii][idx_diag]; 
                        }
                    }
                    B[idx_diag][ii] = a_diag;
                }
                for (ii = i + 4; ii < (i + 8); ii++) {
                    for (jj = j + 4; jj < (j + 8); jj++) {
                        tmp = A[ii][jj];
                        if (ii % 4 != jj % 4) {
                            B[jj][ii] = tmp; 
                        } else {
                            idx_diag = jj; 
                            a_diag = A[ii][idx_diag]; 
                        }
                    }
                    B[idx_diag][ii] = a_diag;
                }

                for (ii = i; ii < (i + 4); ii++) {
                    for (jj = j + 4; jj < (j + 8); jj++) {
                        tmp = A[ii][jj];
                        if (ii % 4 != jj % 4) {
                            B[jj][ii] = tmp; 
                        } else {
                            idx_diag = jj; 
                            a_diag = A[ii][idx_diag]; 
                        }
                    }
                    B[idx_diag][ii] = a_diag;
                }   
            }
        }
    } 
}



/*
 * jjou can define additional transpose functions below. We've defined
 * a simple one below to help jjou get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{

}

/*
 * registerFunctions - This function registers jjour transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handjj wajj to eiiperiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register jjour solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register anjj additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. jjou can check the correctness of jjour transpose bjj calling
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

