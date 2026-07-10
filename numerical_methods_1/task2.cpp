#include <iostream>  
#include <cmath> 

typedef double (*yk_function)(int, double, int);

double y(int A, double x){
    return exp((-A) * x);
}

double yk_1(int A, double h, int k){
    return pow(1 - A*h, k);
}

double yk_2(int A, double h, int k){
    return pow(1 / (1 + A*h), k);
}

double yk_3(int A, double h, int k){
    return pow((2 - A*h) / (2 + A*h), k);
}

double yk_4(int A, double h, int k){
    double D = A*A*h*h + 1;
    double c1 = (1 + sqrt(D)) / (2*sqrt(D));
    double c2 = 1 - c1;

    return c1 * pow((-A)*h + sqrt(D), k) + c2 * pow((-A)*h - sqrt(D), k);
}

double yk_5(int A, double h, int k){
    double a = 1.5 + A*h;
    double c1 = (2*a - 2*a*A*h - 2 + sqrt(4 - 2*a)) / (2*sqrt(4 - 2*a));
    double c2 = 1 - c1;

    return c1 * pow((2 + sqrt(4 - 2*a)) / (2*a), k) + c2 * pow((2 - sqrt(4 - 2*a)) / (2*a), k);
}

double yk_6(int A, double h, int k){
    double c = -1.5 + A*h;
    double c1 = (1 + A*h + sqrt(4 + 2*c)) / (2*sqrt(4 + 2*c));
    double c2 = 1 - c1;

    return c1 * pow(2 - sqrt(4 + 2*c), k) + c2 * pow(2 + sqrt(4 + 2*c), k);
}

void f(int A, int index){
    printf("%d:  ", index);

    double product = 0.0;
    double max_product = 0.0;
    double x_k = 0.0;
    double h = 0.0;

    yk_function yk_funcs[] = {nullptr, yk_1, yk_2, yk_3, yk_4, yk_5, yk_6};

    for (int i = 1; i <= 6; i++){
        if (i == 4){
            i = 6;
        }

        h = pow(10, -i);

        for (int k = 0; k <= pow(10, i); k++){
            product = fabs(y(A, x_k) - yk_funcs[index](A, h, k));

            if (product > max_product){
                max_product = product;
            }

            x_k += h;
        }

        printf("%.3e; ", max_product);

        x_k = 0.0;
        max_product = 0.0;

    }

    printf("\n\n");
}

int main(){
    printf("A = %d\n", 1);
    f(1, 1);
    f(1, 2);
    f(1, 3);
    f(1, 4);
    f(1, 5);
    f(1, 6);
    printf("A = %d\n", 10);
    f(10, 1);
    f(10, 2);
    f(10, 3);
    f(10, 4);
    f(10, 5);
    f(10, 6);
    printf("A = %d\n", 1000);
    f(1000, 1);
    f(1000, 2);
    f(1000, 3);
    f(1000, 4);
    f(1000, 5);
    f(1000, 6);

    return 0;
}