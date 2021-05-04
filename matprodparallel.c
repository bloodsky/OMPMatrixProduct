#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

#define MAX_THS 40

void mul(int m, int n, int p, float *a, float *b, float *c) {
    int i, j, k;
    for (i=0; i<m; i++) {
        for (j=0; j<p; j++) {
            c[j+i*p]=0;
            for (k=0; k<n; k++)
                c[j+i*p] += a[k+i*n]*b[j+k*p];
        }
    }
}

void mul_par(int m, int n, int p, float *a, float *b, float *c) {
    
    int i, j, k;
    #pragma omp parallel shared(a,b,c) private(i,j,k)
    {
        #pragma omp for schedule(static)
        for (i=0; i<m; i++) {
            for (j=0; j<p; j++) {
                c[j+i*p]=0;
                for (k=0; k<n; k++)
                    c[j+i*p] += a[k+i*n]*b[j+k*p];
            }
        }
    }
}

int main() {

    int init_dim = 100;
    int n_rows_a;
    int n_rows_b;
    int n_cols_a;
    int n_cols_b;
    struct timeval start, end;
    struct timezone tz;
    double elapsed_serial, elapsed_parallel;

    FILE *fpt;
    fpt = fopen("MatrixProductSpeedUp.csv", "w+");

    for (int num_th = 5; num_th <= MAX_THS; num_th+=5) {
        omp_set_num_threads(num_th);
        init_dim = 100;
        while(init_dim <= 800) {
            n_rows_a = init_dim;
            n_rows_b = init_dim;
            n_cols_a = init_dim;
            n_cols_b = init_dim;

            float A[n_rows_a*n_cols_a];
            for (int i = 0; i < n_rows_a*n_cols_a; i++) {
                A[i] = i; 
            }
            
            float B[n_rows_b*n_cols_b];
            for (int j = 0; j < n_rows_b*n_cols_b; j++) {
                B[j] = j;
            }   
            float C[n_rows_a*n_cols_b];
            for (int k = 0; k < n_rows_a*n_cols_b; k++) {
                C[k] = 0;
            }

            gettimeofday(&start, &tz);
            mul_par(n_rows_a, n_cols_a, n_cols_b, A, B, C);
            gettimeofday(&end, &tz);
            
            elapsed_parallel = (double) (end.tv_sec-start.tv_sec) + (double) (end.tv_usec-start.tv_usec) * 1.e-6;
            //printf("parallel elapsed time = %f seconds.\n", elapsed_parallel);

            gettimeofday(&start, &tz);
            mul(n_rows_a, n_cols_a, n_cols_b, A, B, C);
            gettimeofday(&end, &tz);
            
            // megaflop conversion 
            elapsed_serial = (double) (end.tv_sec-start.tv_sec) + (double) (end.tv_usec-start.tv_usec) * 1.e-6;
            //printf("serial elapsed time = %f seconds.\n", elapsed_serial);
            double sp = elapsed_serial/elapsed_parallel;
            //printf("Speedup = %f\n",sp);
            
            fprintf(fpt,"%d, %d, %f\n",num_th,init_dim,sp);
            init_dim += 100;
        }
    }
    fclose(fpt);
}
