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
    return 1;
}

double f_1(double x){
    return x;
}

double f_2(double x){
    return x * x;
}

double f_3(double x){
    return x * x * x;
}

double f_5(double x){
    return x * x * x * x * x;
}

double f_9(double x){
    return x * x * x * x * x * x * x * x * x;
}

double simpson(double a, double b, double (*f)(double)){
    return (b - a) / 6 * (f(a) + 4 * f(a/2 + b/2) + f(b));
}

double gauss(double a, double b, double (*f)(double)){
    double x_0 = (a + b) / 2;
    double x_1 = (a + b) / 2 - (b - a) / 2 * sqrt(3.0/ 5.0);
    double x_2 = (a + b) / 2 + (b - a) / 2 * sqrt(3.0 / 5.0);

    return (b - a) / 18 * (5 * f(x_1) + 8 * f(x_0) + 5 * f(x_2));
}


int main(){
    double a = 1.0;
    double b = 1.1;

    printf("%lf   %lf   %e   %e\n\n", simpson(a, b, f_0), gauss(a, b, f_0), simpson(a, b, f_0) - 0.1, gauss(a, b, f_0) - 0.1);
    printf("%lf   %lf   %e   %e\n\n", simpson(a, b, f_1), gauss(a, b, f_1), simpson(a, b, f_1) - 0.105, gauss(a, b, f_1) - 0.105);
    printf("%lf   %lf   %e   %e\n\n", simpson(a, b, f_2), gauss(a, b, f_2), simpson(a, b, f_2) - 331.0/3000.0, gauss(a, b, f_2) - 331.0/3000.0);
    printf("%lf   %lf   %e   %e\n\n", simpson(a, b, f_3), gauss(a, b, f_3), simpson(a, b, f_3) - 4641.0/40000.0, gauss(a, b, f_3) - 4641.0/40000.0);
    printf("%lf   %lf   %e   %e\n\n", simpson(a, b, f_5), gauss(a, b, f_5), simpson(a, b, f_5) - 257187.0/2000000.0, gauss(a, b, f_5) - 257187.0/2000000.0);
    printf("%lf   %lf   %e   %e\n", simpson(a, b, f_9), gauss(a, b, f_9), simpson(a, b, f_9) - 15937424601.0/100000000000.0, gauss(a, b, f_9) - 15937424601.0/100000000000.0);

    return 0;
}