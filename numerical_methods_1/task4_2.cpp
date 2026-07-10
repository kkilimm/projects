#include <iostream>  
#include <cmath>  
#include <fstream>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double u_true(double t, double x){
    return x * (x-1) * exp(2*t);
}

double u_0(double x){
    return x * (x-1);
}

double f(double t, double x){
    return 2 * x * (x-1) * exp(2*t) - 2 * exp(2*t);
}

double norma(double* u2, double* u, double t, int M){
    double S = 0.0;
    for (int i = 0; i <= M; i++){
        S += (u2[i] - u[i]) * (u2[i] - u[i]) * t;
    }
    return sqrt(S);
    
}

void create_matrix(double* a1, double* a2, double* a3, double* b, double t, double h, int M, double* u1, int i, double* t_n, double* x_m){
    a2[0] = 1.0;
    for (int j = 1; j <= M - 1; j++){
        a2[j] = (1/t) + 2 / (h*h);
    }
    a2[M] = 1.0;

    for (int j = 0; j <= M - 2; j++){
        a1[j] = - 1 / (h*h);
    }
    a1[M-1] = 0.0;

    a3[0] = 1.0;
    for (int j = 1; j <= M - 1; j++){
        a3[j] = - 1 / (h*h);
    }

    b[0] = 0.0;
    for (int j = 1; j <= M - 1; j++){
        b[j] = f(t_n[i], x_m[j]) + u1[j] / t;
    }
    b[M] = 0.0;
}

void step(double* a1, double* a2, double* a3, double* b, double* u2, int M){
    for (int j = 1; j <= M; j++){
        b[j] = b[j] - b[j-1] * a1[j-1] / a2[j-1];

        a2[j] = a2[j] - a1[j-1] * a3[j-1] / a2[j-1];

        a1[j-1] = 0.0;
    }

    u2[M] = b[M] / a2[M];
    for (int j = M - 1; j >= 0; j--){
        u2[j] = 1 / a2[j] * (b[j] - u2[j+1] * a3[j]);
    }
}

int main() {

    std::ofstream file_u("u.txt");
    std::ofstream file_x_m("x_m.txt");
    std::ofstream file_t_n("t_n.txt");

    int M = 100;
    int N = 3 * M * M;

    double h = 1.0 / (M - 0.5);
    double t = 1.0 / N;

    double* u1 = (double*)calloc(M + 1, sizeof(double));
    double* u2 = (double*)calloc(M + 1, sizeof(double));

    double x_0 = -0.5 * h;
    double t_0 = 0.0;

    double* x_m = (double*)calloc(M + 1, sizeof(double));
    double* t_n = (double*)calloc(N + 1, sizeof(double));

    for (int i = 0; i <= M; i++) {
        x_m[i] = x_0;
        file_x_m << x_m[i] << "\n";
        x_0 += h;
    }

    for (int i = 0; i <= N; i++) {
        t_n[i] = t_0;
        file_t_n << t_n[i] << "\n";
        t_0 += t;
    }
    
    for (int i = 0; i <= M; i++){
        u1[i] = u_0(x_m[i]);
        file_u << u1[i] << " ";
    }

    file_u << "\n";

    double* a1 = (double*)calloc(M, sizeof(double));
    double* a2 = (double*)calloc(M + 1, sizeof(double));
    double* a3 = (double*)calloc(M, sizeof(double));
    double* b = (double*)calloc(M + 1, sizeof(double));

    for (int i = 1; i <= N; i++){
        create_matrix(a1, a2, a3, b, t, h, M, u1, i, t_n, x_m);
        step(a1, a2, a3, b, u2, M);
        for (int i = 0; i <= M; i++){
            file_u << u2[i] << " ";
            u1[i] = u2[i];
        }
        file_u << "\n";
    }

    double* u = (double*)calloc(M + 1, sizeof(double));

    for (int i = 0; i <= M; i++){
        u[i] = u_true(1, x_m[i]);
    }

    printf("h = %lf; t = %lf\n", h, t);
    printf("norma = %e\n", norma(u2, u, t, M));

    free(u1);
    free(u2);
    free(u);
    free(x_m);
    free(t_n);
    free(a1);
    free(a2);
    free(a3);
    free(b);

    return 0;
}