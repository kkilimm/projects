#include <iostream> 
#include <cstdlib> 
#include <cmath>  
#include <fstream>
#include <ctime>
#include <algorithm>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double f_0(double x){
    return exp(x);
}

double f_1(double x){
    return cos(100 * x);
}

double f_2(double x){
    return exp(-1000 * x);
}

double f_3(double x){
    return 1 / sqrt(1 - x*x);
}

double fun_simpson(double a_i, double b_i, double (*f)(double)){
    return (b_i - a_i) / 6 * (f(a_i) + 4 * f(a_i/2 + b_i/2) + f(b_i));
}

double fun_gauss(double a_i, double b_i, double (*f)(double)){
    double x_0 = (a_i + b_i) / 2;
    double x_1 = (a_i + b_i) / 2 - (b_i - a_i) / 2 * sqrt(3.0 / 5.0);
    double x_2 = (a_i + b_i) / 2 + (b_i - a_i) / 2 * sqrt(3.0 / 5.0);

    return (b_i - a_i) / 18 * (5 * f(x_1) + 8 * f(x_0) + 5 * f(x_2));
}

void integral(double a, int N, double h, double res, double (*f)(double)){
    double S_simpson = 0.0;
    double S_gauss = 0.0;

    double a_i = a;
    double b_i = a + h;

    for (int i = 0; i < N; i++){
        S_simpson += fun_simpson(a_i, b_i, f);
        S_gauss += fun_gauss(a_i, b_i, f);

        a_i += h;
        b_i += h;
    }

    printf("%e\n", S_simpson - res);
    printf("%e\n", S_gauss - res);
    printf("\n----------\n");
}


int main(){

    int n;
    scanf("%d", &n);

    if (n==1){

        double a = 0.0;
        double b = PI;
        int N = 20;
        double h = (b - a) / N;

        integral(a, N, h, 0.0, f_1);
    }

    if (n==2){

        double a = 0.0;
        double b = 1.0;
        int N = 20;
        double h = (b - a) / N;

        integral(a, N, h, 0.001, f_2);
    }

    if (n==3){

        double a = -1.0;
        double b = 1.0;
        int N = 20;
        double h = (b - a) / N;

        integral(a, N, h, PI, f_3);
    }

    if (n==0){

        double a = 0.0;
        double b = 1.0;
        int N = 10;
        double h = (b - a) / N;

        integral(a, N, h, exp(1) - 1, f_0);

        N *= 2;
        h = (b - a) / N;

        integral(a, N, h, exp(1) - 1, f_0);
    }

    return 0;
}