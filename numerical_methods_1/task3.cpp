#include <iostream>  
#include <cmath>
#include <fstream>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double f(double x, double y){
    return 2 * (2-x) * y + (x + 2) * exp(-x*x) * (1 / sqrt(2 * PI));
}

void step(double& y, double y_0, double x_0, double h, std::ofstream& file_E){
    double k1 = h * f(x_0, y_0);
    double k2 = h * f(x_0 + 0.5*h, y_0 + 0.5*k1);
    double k3 = h * f(x_0 + 0.5*h, y_0 + 0.5*k2);
    double k4 = h * f(x_0 + h, y_0 + k3);

    y = y_0 + (k1 + 2*k2 + 2*k3 + k4) / 6;

    double E = (k1 - 4*k2 + 2*k3 + k4) / 6;

    file_E << E << "\n";
}

int main(){

    std::ofstream file_x("x.txt");
    std::ofstream file_y("y.txt");
    std::ofstream file_E("E.txt");

    double x_0 = 1.0;
    double y_0 = 10.0;
    double y;
    double h = 0.5;
    double X = 5.0;

    file_x << x_0 << "\n";
    file_y << y_0 << "\n";

    for (int i = 1; i <= X / h; i += 1){
        step(y, y_0, x_0, h, file_E);

        file_y << y << "\n";

        y_0 = y;

        x_0 += h;

        file_x << x_0 << "\n";
    }

    file_x.close();
    file_y.close();
    file_E.close();

    return 0;
}