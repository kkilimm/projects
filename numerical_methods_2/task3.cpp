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
    return fabs(x);
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

void print_array(int* A, int N){

    printf("[");

    for (int i = 0; i < N; i++){
        printf("%d;   ", A[i]);
    }

    printf("]");

    printf("\n\n");
    printf("---");
    printf("\n\n");
}

void print(double* X, double* Y, double* A, int n, int* ind, std::ofstream& file){

    for (int i = 0; i < n - 1; i++) {

        double h = (X[ind[i + 1]] - X[ind[i]]) / 3.0;

        file << X[ind[i]] << " " << Y[ind[i]] << " " << P_nminus1(X[ind[i]], A, n) << " " << Y[ind[i]] - P_nminus1(X[ind[i]], A, n) << "\n";

        file << X[ind[i]] + h << " " << f(X[ind[i]] + h) << " " << P_nminus1(X[ind[i]] + h, A, n) << " " << f(X[ind[i]] + h) - P_nminus1(X[ind[i]] + h, A, n) << "\n";

        file << X[ind[i]] + 2*h << " " << f(X[ind[i]] + 2*h) << " " << P_nminus1(X[ind[i]] + 2*h, A, n) << " " << f(X[ind[i]] + 2*h) - P_nminus1(X[ind[i]] + 2*h, A, n) << "\n";

    }

    file << X[ind[n - 1]] << " " << Y[ind[n - 1]] << " " << P_nminus1(X[ind[n - 1]], A, n) << " " << Y[ind[n - 1]] - P_nminus1(X[ind[n - 1]], A, n) << "\n";

}

double** create_matrix(double* X, double* Y, int n, int* ind){

    double** B = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        B[i] = (double*)calloc(n + 1, sizeof(double));;
    }

    double x = 1.0;

    for (int i = 0; i < n; i++) {
        B[i][0] = 1.0;
        B[i][n] = Y[ind[i]];
        B[i][n - 1] = x;
        x *= -1.0;
    }

    for (int i = 0; i < n; i++){
        x = X[ind[i]];
        for (int j = 1; j < n - 1; j++){
            B[i][j] = x;
            x *= X[ind[i]];
        }
    }

    return B;

}

void method(double* A, int n, double* X, double* Y, int* ind){

    double** B = create_matrix(X, Y, n, ind);
    double** B_0 = create_matrix(X, Y, n, ind);

    //print_matrix(B, N);

    // прямой ход

    for (int i = 0; i < n - 1; i++){

        int max_row = i;
        for(int j = i + 1; j < n; j++){
            if (B[j][i] <= B[max_row][i]){
                max_row = j;
            }
        }

        std::swap(B[i], B[max_row]);

        double flag1 = B[i][i];
        for (int j = i; j < n + 1; j++){
            B[i][j] /= flag1;
        }


        for (int j = i + 1; j < n; j++){
            double flag2 = B[j][i];
            for(int k = i; k < n + 1; k++){
                B[j][k] -= B[i][k] * flag2;
            }
        }

    }

    // обратный ход

    A[n - 1] = B[n - 1][n] / B[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--){
        A[i] = B[i][n];

        for (int j = n - 1; j >= i + 1; j--){
            A[i] -= A[j] * B[i][j];
        }

        A[i] /= B[i][i];
    }

    //print_array(A, N);

    printf("%e\n", norma(B_0, A, n));

    // очистка памяти

    for (int i = 0; i < n; i++) {
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

double search_fi(double* A, int n, int N, double* X){

    double fi = f(X[0]) - P_nminus1(X[0], A, n);

    for (int i = 1; i < N; i++){
        if (fabs(f(X[i]) - P_nminus1(X[i], A, n)) > fabs(fi)){
            fi = f(X[i]) - P_nminus1(X[i], A, n);
        }
    }

    return fi;
}

void function(int N, int n, int* ind, double* A, double* X, double* Y){

    for (int i = 0; i < n; i++){
        ind[i] = (N / n) * i;
    }

    method(A, n, X, Y, ind);

    double h = Y[ind[0]] - P_nminus1(X[ind[0]], A, n);

    double fi = search_fi(A, n, N, X);
    
    while (fabs(h - fi) / fabs(fi) > 0.001){ 

        //printf("h = %lf; fi = %lf\n", h, fi);

        //print_array(ind, n);

        bool flag = false;

        for(int j = 0; j < ind[0]; j++){

            if (fabs(f(X[j]) - P_nminus1(X[j], A, n)) == fabs(fi)){

                    if ((f(X[j]) - P_nminus1(X[j], A, n)) * h > 0){
                        ind[0] = j;
                    }

                    else{
                        ind[0] = j;
                        for(int i = 1; i < n; i++){
                            ind[i] = ind[i - 1];
                        }
                    }

                    flag = true;
                    
                    break;
                }
        }

        if (flag == true){

            method(A, n, X, Y, ind);

            h = Y[ind[0]] - P_nminus1(X[ind[0]], A, n);

            fi = search_fi(A, n, N, X);

            continue;
        }

        for (int i = 0; i < n - 1; i++){

            for (int j = ind[i] + 1; j < ind[i + 1]; j++){

                if (fabs(f(X[j]) - P_nminus1(X[j], A, n)) == fabs(fi)){

                    if ((f(X[j]) - P_nminus1(X[j], A, n)) * (Y[ind[i]] - P_nminus1(X[ind[i]], A, n)) > 0){
                        ind[i] = j;
                    }

                    else{
                        ind[i + 1] = j;
                    }

                    flag = true;
                    
                    break;
                }
            }
        }

        if (flag == true){
            
            method(A, n, X, Y, ind);

            h = Y[ind[0]] - P_nminus1(X[ind[0]], A, n);

            fi = search_fi(A, n, N, X);
            
            continue;

        }

        for(int j = ind[n - 1] + 1; j < N; j++){

            if (fabs(f(X[j]) - P_nminus1(X[j], A, n)) == fabs(fi)){

                if ((f(X[j]) - P_nminus1(X[j], A, n)) * (Y[ind[n - 1]] - P_nminus1(X[ind[n - 1]], A, n)) > 0){
                        ind[n - 1] = j;
                    }

                else{
                    ind[n - 1] = j;
                    for(int i = 0; i < n - 1; i++){
                        ind[i] = ind[i + 1];
                    }
                }
                    
                flag = true;

                break;

            }
        }

        if (flag == true){
            
            method(A, n, X, Y, ind);

            h = Y[ind[0]] - P_nminus1(X[ind[0]], A, n);

            fi = search_fi(A, n, N, X);

        }

    }
}


int main(){

    int q = 1;
    double a = -1.0;
    double b = 1.0;
    int N = 1001;
    int n = 7;

    double* X = (double*)calloc(N, sizeof(double));
    double* Y = (double*)calloc(N, sizeof(double));
    double* A = (double*)calloc(N, sizeof(double));
    int* ind = (int*)calloc(n, sizeof(int));

    std::ofstream file("file3.txt");

    fun(q, X, Y, a, b, N);

    function(N, n, ind, A, X, Y);

    print(X, Y, A, n, ind, file);

    /*for (int i = 0; i < n; i++) {
        printf("%25.15lf ", X[ind[i]]);
        printf("%25.15lf ", Y[ind[i]]);
        printf("%25.15lf\n", P_nminus1(X[ind[i]], A, n));
    }*/

    file.close();

    free(X);
    free(Y);
    free(A);
    free(ind);

    return 0;
}