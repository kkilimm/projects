#include <iostream>  
#include <cmath>
#include <fstream>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

void fun(double* f, double* y_0, double x_0){
    f[0] = y_0[1] + y_0[0];
    f[1] = y_0[1] - y_0[0];
    f[2] = 2 * y_0[2] - exp(x_0);
}

void step(double* y, double* y_0, double x_0, double h, int N, std::ofstream& file_E){
    double* k1 = (double*)malloc((N) * sizeof(double));
    double* k2 = (double*)malloc((N) * sizeof(double));
    double* k3 = (double*)malloc((N) * sizeof(double));
    double* k4 = (double*)malloc((N) * sizeof(double));

    double* f = (double*)malloc((N) * sizeof(double));

    double* tmp = (double*)malloc((N) * sizeof(double));

    double* E = (double*)malloc((N) * sizeof(double));

    fun(f, y_0, x_0);

    for (int i = 0; i < N; i++){
        k1[i] = h * f[i];
    }

    for (int i = 0; i < N; i++){
        tmp[i] = y_0[i] + 0.5 * k1[i];
    }

    fun(f, tmp, x_0 + 0.5*h);

    for(int i = 0; i < N; i++){
        k2[i] = h * f[i];
    }

    for (int i = 0; i < N; i++){
        tmp[i] = y_0[i] + 0.5 * k2[i];
    }

    fun(f, tmp, x_0 + 0.5*h);

    for(int i = 0; i < N; i++){
        k3[i] = h * f[i];
    }

    for (int i = 0; i < N; i++){
        tmp[i] = y_0[i] + k3[i];
    }

    fun(f, tmp, x_0 + h);

    for(int i = 0; i < N; i++){
        k4[i] = h * f[i];
    }

    for (int i = 0; i < N; i++){
        y[i] = y_0[i] + (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]) / 6;
    }

    for (int i = 0; i < N; i++){
        E[i] = (k1[i] - 4*k2[i] + 2*k3[i] + k4[i]) / 6;

        file_E << E[i] << " ";
    }

    file_E << "\n";

    free(k1);
    free(k2);
    free(k3);
    free(k4);
    free(f);
    free(tmp);
    free(E);
}

double norma(double* y_true, double* y, int N){
    double S = 0;
    for (int i = 0; i < N; i++){
        S += (y_true[i] - y[i]) * (y_true[i] - y[i]);
    }
    S = sqrt(S);

    return S;
}

int main(){

    std::ofstream file_x("x.txt");
    std::ofstream file_y("y.txt");
    std::ofstream file_E("E.txt");

    int N = 3;

    double x_0 = 0;

    double* y_0 = (double*)malloc((N) * sizeof(double));

    y_0[0] = 0;
    y_0[1] = 1;
    y_0[2] = 1;

    double h = 0.0001;
    double X = 1; 

    double* y = (double*)malloc((N) * sizeof(double));

    file_x << x_0 << "\n";
    file_y << y_0[0] << " " << y_0[1] << " " << y_0[2] << "\n";

    for (int i = 1; i <= X / h; i += 1){
        step(y, y_0, x_0, h, N, file_E);

        file_y << y[0] << " " << y[1] << " " << y[2] << "\n";

        for (int i = 0; i < N; i++){
            y_0[i] = y[i];
        }

        x_0 += h;

        file_x << x_0 << "\n";
    }

    y_0[0] = sin(1) * exp(1);
    y_0[1] = cos(1) * exp(1);
    y_0[2] = exp(1);

    printf("h = %lf\n", h);
    printf("%e\n", norma(y_0, y, N));

    file_x.close();
    file_y.close();
    file_E.close();

    free(y_0);
    free(y);

    return 0;
}