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
    return sin(x) - cos(1)*x;
}

double fi_j_m(double j, int m, int N){
    return sqrt(2) * sin((PI + 2 * PI * m) * j / (2 * N - 1));
}

void add_c_m(int N, double* c_m, double* Y, double h){

    for (int m = 0; m < N - 1; m++){       
    
        double S = 0.0;

        for(int j = 0; j < N - 1; j++){
            S += Y[j + 1] * fi_j_m(j + 1, m, N);
        }

        c_m[m] = S * h;
    }
}

double function(double j, int N, double* c_m){
    
    double S = 0.0;

    for (int m = 0; m < N - 1; m++){
        S += c_m[m] * fi_j_m(j, m, N);
    }

    return S;
}

void fun(double* X, double* Y, double a, int N, double h) {

        X[0] = a;
        Y[0] = f(a);

        for (int i = 1; i < N + 1; i++) {
            X[i] = X[i - 1] + h;
            Y[i] = f(X[i]);
        }
    }

void print(double* X, double* Y, double* c_m, int N, int j, double* delta_array, std::ofstream& file){

    double delta = 0.0;

    for (int i = 0; i < N; i++) {

        double h = (X[i + 1] - X[i]) / 3.0;

        file << X[i] << " " << Y[i] << " " << function(i, N, c_m) << " " << Y[i] - function(i, N, c_m) << "\n";

        file << X[i] + h << " " << f(X[i] + h) << " " << function(i + 0.333333, N, c_m) << " " << f(X[i] + h) - function(i + 0.333, N, c_m) << "\n";

        if (fabs(delta) < fabs (f(X[i] + h) - function(i + 0.333, N, c_m))){
            delta = f(X[i] + h) - function(i + 0.333, N, c_m);
        }

        file << X[i] + 2*h << " " << f(X[i] + 2*h) << " " << function(i + 0.666666, N, c_m) << " " << f(X[i] + 2*h) - function(i + 0.666, N, c_m) << "\n";

        if (fabs(delta) < fabs (f(X[i] + 2*h) - function(i + 0.666, N, c_m))){
            delta = f(X[i] + 2*h) - function(i + 0.666, N, c_m);
        }

    }

    file << X[N] << " " << Y[N] << " " << function(N, N, c_m) << " " << Y[N] - function(N, N, c_m) << "\n" << "\n" << "----------" << "\n" << "\n";

    delta_array[j] = delta;

}

void print_array(double* delta_array){

    for (int i = 0; i < 4; i++){
        printf("%lf   ", delta_array[i]);
    }
}

int main(){

    double a = 0.0;
    double b = 1.0;
    int N = 1;
    double h = 0.0;

    double* delta_array = (double*)calloc(4, sizeof(double));

    std::ofstream file("file4.txt");

    for (int j = 0; j < 4; j++){

        N *= 10;
        h = 1.0 / (N - 0.5);

        double* X = (double*)calloc(N + 1, sizeof(double));
        double* Y = (double*)calloc(N + 1, sizeof(double));
        double* c_m = (double*)calloc(N - 1, sizeof(double));

        fun(X, Y, a, N, h);

        add_c_m(N, c_m, Y, h);

        print(X, Y, c_m, N, j, delta_array, file);

        free(X);
        free(Y);
        free(c_m);
    }

    print_array(delta_array);

    file.close();
    free(delta_array);

    return 0;
}