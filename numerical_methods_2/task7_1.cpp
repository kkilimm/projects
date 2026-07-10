#include <iostream> 
#include <cstdlib> 
#include <cmath>  
#include <fstream>
#include <ctime>
#include <algorithm>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double f1(double x){
    return (x - 3) * (x - 3);
}

double df1(double x){
    return 2 * (x - 3);
}

double f2(double x){
    return (x - 3) * (x - 3) * (x - 5);
}

double df2(double x){
    return 3 * x*x - 22*x + 39;
}

int NewtonRaphson(double x, double z, double (*f)(double), double (*df)(double), double eps, std::ofstream& file){

    for (int i = 0; i < 200; i++){

        double x_next = x - f(x) / df(x);

        file << fabs(z - x_next) << "\n";
        
        double delta = x_next - x;

        x = x_next;

        if (fabs(delta) < eps){

            printf("%lf\n", x);

            return 0;
        }

    }

    return -1;

}


int main(){

    double x = 1.0;
    double eps = 1e-15;
    double z1 = 3.0;
    double z2 = 5.0;

    std::ofstream file("file7.txt");

    NewtonRaphson(x, z1, f1, df1, eps, file);

    file.close();

    return 0;
}