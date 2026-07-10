#include <iostream> 
#include <cstdlib> 
#include <cmath>  
#include <fstream>
#include <ctime>
#include <algorithm>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double f(double x){
    return x * x * x * x * x * x;
}

double norma(double** B, double* A, int N){
    double S;
    double* Ax = (double*)calloc(N + 1, sizeof(double));

    for (int i = 0; i < N; i++){
        S = 0.0;
        for (int j = 0; j < N; j++){
            S += B[i][j] * A[j];
        }
        Ax[i] = S;
    }

    S = 0.0;

    for (int i = 0; i < N; i++){
        S += (Ax[i] - B[i][N]) * (Ax[i] - B[i][N]);
    }

    free(Ax);

    return sqrt(S);
}

double P_nminus1(double X_i, double* A, int N){
    double S = 0.0;
    double x = X_i;

    S += A[0];
    for (int i = 1; i < N - 1; i++) {
        S += A[i] * x;
        x *= X_i;
    }

    return S;
}

void print_matrix(double** B, int N){

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N + 1; j++){
                printf("%lf ", B[i][j]);
        }

        printf("\n");
    }

    printf("\n\n");
    printf("---");
    printf("\n\n");
}

void print_array(double* A, int N){

    for (int i = 0; i < N; i++){
        printf("%lf   ", A[i]);
    }

    printf("\n\n");
    printf("---");
    printf("\n\n");
}

void print(double* X, double* Y, double* A, int N, std::ofstream& file){

    for (int i = 0; i < N - 1; i++) {

        double h = (X[i + 1] - X[i]) / 3.0;

        file << X[i] << " " << Y[i] << " " << P_nminus1(X[i], A, N) << " " << Y[i] - P_nminus1(X[i], A, N) << "\n";

        file << X[i] + h << " " << f(X[i] + h) << " " << P_nminus1(X[i] + h, A, N) << " " << f(X[i] + h) - P_nminus1(X[i] + h, A, N) << "\n";

        file << X[i] + 2*h << " " << f(X[i] + 2*h) << " " << P_nminus1(X[i] + 2*h, A, N) << " " << f(X[i] + 2*h) - P_nminus1(X[i] + 2*h, A, N) << "\n";

    }

    file << X[N - 1] << " " << Y[N - 1] << " " << P_nminus1(X[N - 1], A, N) << " " << Y[N - 1] - P_nminus1(X[N - 1], A, N) << "\n";

}

double** create_matrix(double* X, double* Y, int N){

    double** B = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        B[i] = (double*)calloc(N + 1, sizeof(double));;
    }

    double x = 1.0;

    for (int i = 0; i < N; i++) {
        B[i][0] = 1.0;
        B[i][N] = Y[i];
        B[i][N - 1] = x;
        x *= -1.0;
    }

    for (int i = 0; i < N; i++){
        x = X[i];
        for (int j = 1; j < N - 1; j++){
            B[i][j] = x;
            x *= X[i];
        }
    }

    return B;

}

void method(double* A, int N, double* X, double* Y){

    double** B = create_matrix(X, Y, N);
    double** B_0 = create_matrix(X, Y, N);

    //print_matrix(B, N);

    // прямой ход

    for (int i = 0; i < N - 1; i++){

        int max_row = i;
        for(int j = i + 1; j < N; j++){
            if (B[j][i] <= B[max_row][i]){
                max_row = j;
            }
        }

        std::swap(B[i], B[max_row]);

        double flag1 = B[i][i];
        for (int j = i; j < N + 1; j++){
            B[i][j] /= flag1;
        }


        for (int j = i + 1; j < N; j++){
            double flag2 = B[j][i];
            for(int k = i; k < N + 1; k++){
                B[j][k] -= B[i][k] * flag2;
            }
        }

    }

    // обратный ход

    A[N - 1] = B[N - 1][N] / B[N - 1][N - 1];

    for (int i = N - 2; i >= 0; i--){
        A[i] = B[i][N];

        for (int j = N - 1; j >= i + 1; j--){
            A[i] -= A[j] * B[i][j];
        }

        A[i] /= B[i][i];
    }

    //print_array(A, N);

    printf("%e\n", norma(B_0, A, N));

    // очистка памяти

    for (int i = 0; i < N; i++) {
        free(B[i]);
        free(B_0[i]);
    }
    free(B);
    free(B_0);
}

void fun(int q, double* X, double* Y, double a, double b, int N) {

    if (q == 1){

        double h = (b - a) / (N - 1);
        double x_0 = a;

        for (int i = 0; i < N; i++) {
            X[i] = x_0;
            Y[i] = f(X[i]);
            x_0 += h;
        }
    }

    if (q == 2){

        for (int k = N; k >= 1; k--) {
            X[N - (k - 1) - 1] = ((a + b) / 2.0) + (((b - a) / 2.0) * cos((2.0 * k - 1.0) / (2.0 * N) * PI));
        }

        for (int k = 0; k < N; k++) {
            Y[k] = f(X[k]); 
        }

    }

    if (q == 3){

        srand(time(0));

        for (int i = 0; i < N; i++) {
            X[i] = a + (b - a) * (rand() / (double)RAND_MAX);
        }

        std::sort(X, X + N);

        for (int i = 0; i < N; i++) {
            Y[i] = f(X[i]); 
        }
    }

}

int main(){

    int q = 1;
    int N = 6;
    double a = -1.0;
    double b = 1.0;

    N += 1;

    double* X = (double*)calloc(N, sizeof(double));
    double* Y = (double*)calloc(N, sizeof(double));
    double* A = (double*)calloc(N, sizeof(double));

    std::ofstream file("file2.txt");

    fun(q, X, Y, a, b, N);

    method(A, N, X, Y);

    print(X, Y, A, N, file);

    /*for (int i = 0; i < N; i++) {
        printf("%25.15lf ", X[i]);
        printf("%25.15lf ", Y[i]);
        printf("%25.15lf\n", P_nminus1(X[i], A, N));
    }*/

    file.close();

    free(X);
    free(Y);
    free(A);

    return 0;
}