#include <iostream> 
#include <cstdlib> 
#include <cmath>  
#include <fstream>
#include <ctime>
#include <algorithm>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

void sum(double* x_next, double* x, int N){
    
    for (int i = 0; i < N; i++){
        x_next[i] += x[i];
    }
}

void equal(double* x, double* x_next, int N){

    for (int i = 0; i < N; i++){
        x[i] = x_next[i];
    }
}

double max(double* x_next, double* x, int N){

    double max = fabs(x_next[0] - x[0]);

    for (int i = 1; i < N; i++){

        if (fabs(x_next[i] - x[i]) >= max){
            max = fabs(x_next[i] - x[i]);
        }
    }

    return max;
}

void fun_f(double* f, double* x, int N) {

    f[0] = x[0]*x[0] + x[1]*x[1] - 4; 
    f[1] = x[0] - x[1];           

}

void fun_x_before(double* x, double* x_before, double h, int N, int flag) {
    
    equal(x_before, x, N);

    x_before[flag] -= h;
}

void fun_x_after(double* x, double* x_after, double h, int N, int flag) {

    equal(x_after, x, N);

    x_after[flag] += h;
}

double** create_matrix(int N){

    double** df = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        df[i] = (double*)calloc(N + 1, sizeof(double));;
    }

    return df;
}

void print_array(double* x, int N){

    for (int i = 0; i < N; i++){
        printf("%lf   ", x[i]);
    }

    printf("\n\n");
    printf("---");
    printf("\n\n");
}

void print_matrix(double** W, int N){

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N + 1; j++){
                printf("%lf ", W[i][j]);
        }

        printf("\n");
    }

    printf("\n\n");
    printf("---");
    printf("\n\n");
}

void made_matrix(double** df, double* x, int N){

    double h = 1e-5;

    double* f = (double*)calloc(N, sizeof(double));
    fun_f(f, x, N);

    double* f_before = (double*)calloc(N, sizeof(double));
    double* f_after = (double*)calloc(N, sizeof(double));

    double* x_before = (double*)calloc(N, sizeof(double));
    double* x_after = (double*)calloc(N, sizeof(double));

    for (int j = 0; j < N; j++){

        fun_x_before(x, x_before, h, N, j);
        fun_x_after(x, x_after, h, N, j);

        fun_f(f_before, x_before, N);
        fun_f(f_after, x_after, N);

        for (int i = 0; i < N; i++){
            df[i][j] = (f_after[i] - f_before[i]) / (2*h);
        }
        
    }

    for (int i = 0; i < N; i++){
        df[i][N] = -f[i];
    }

    free(f);
    free(f_before);
    free(f_after);
    free(x_before);
    free(x_after);
}

void method(double* x, int N, double** W){

    // прямой ход

    for (int i = 0; i < N - 1; i++){

        int max_row = i;
        for(int j = i + 1; j < N; j++){
            if (W[j][i] <= W[max_row][i]){
                max_row = j;
            }
        }

        std::swap(W[i], W[max_row]);

        double flag1 = W[i][i];
        for (int j = i; j < N + 1; j++){
            W[i][j] /= flag1;
        }


        for (int j = i + 1; j < N; j++){
            double flag2 = W[j][i];
            for(int k = i; k < N + 1; k++){
                W[j][k] -= W[i][k] * flag2;
            }
        }

    }

    // обратный ход

    x[N - 1] = W[N - 1][N] / W[N - 1][N - 1];

    for (int i = N - 2; i >= 0; i--){
        x[i] = W[i][N];

        for (int j = N - 1; j >= i + 1; j--){
            x[i] -= x[j] * W[i][j];
        }

        x[i] /= W[i][i];
    }

    //print_array(x, N);
}

int root(double* x, double* x_next, int N, double eps){

    double** df = create_matrix(N);

    for (int i = 0; i < 200; i++){
        
        made_matrix(df, x, N);

        method(x_next, N, df);

        sum(x_next, x, N);

        if (max(x_next, x, N) < eps){

            equal(x, x_next, N);

            print_array(x, N);

            for (int i = 0; i < N; i++) {
                free(df[i]);
            }
            free(df);
            
            return 0;
        }

        equal(x, x_next, N);

        print_array(x, N);

    }

    for (int i = 0; i < N; i++) {
        free(df[i]);
    }
    free(df);

    return -1;
}


int main(){

    int N = 2;
    double eps = 1e-15;

    double* x = (double*)calloc(N, sizeof(double));

    x[0] = 1.0;
    x[1] = 1.0;

    double* x_next = (double*)calloc(N, sizeof(double));

    root(x, x_next, N, eps);

    free(x);
    free(x_next);

    return 0;
}