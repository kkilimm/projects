#include <iostream>  
#include <cmath>  
#include <fstream>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double u_true(double t, double x){
    return x * sin(PI * x) * sin(t);
}

double u_0(double x){
    (void) x;
    return 0;
}

double f(double t, double x){
    return  x * sin(PI * x) * cos(t) - sin(t) * (2 * PI * cos(PI*x) - PI * PI * x * sin(PI*x));
}

double step(double u_m_minus_1, double u_m, double u_m_plus_1, double t, double h, double f){
    return (f + u_m * (1/t - 2/(h*h)) + (u_m_minus_1 + u_m_plus_1) / (h*h)) / (1/t);
}

double norma(double* u2, double* u, double t, int M){
    double S = 0.0;
    for (int i = 0; i <= M; i++){
        S += (u2[i] - u[i]) * (u2[i] - u[i]) * t;
    }
    return sqrt(S);
    
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

    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M - 1; j++){
            u2[j] = step(u1[j-1], u1[j], u1[j+1], t, h, f(t_n[i-1], x_m[j]));
            if (j == 1){
                file_u << -u2[j] << " ";
            }
            file_u << u2[j] << " ";
        }
        u2[0] = -u2[1];
        file_u << "\n";

        for (int i = 0; i <= M; i++){
            u1[i] = u2[i];
        }
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

    return 0;
}