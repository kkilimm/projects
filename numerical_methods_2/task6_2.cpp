#include <iostream> 
#include <cstdlib> 
#include <cmath>  
#include <fstream>
#include <ctime>
#include <algorithm>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double f(double x1, double x2){
    return x1*x1*x1*x1 + x1*x1*x2*x2 + x2*x2*x2*x2;
}

double square(int* arr_triangle_i, double** arr_node){
    double x_1 = arr_node[arr_triangle_i[0]][0];
    double y_1 = arr_node[arr_triangle_i[0]][1];
    double x_2 = arr_node[arr_triangle_i[1]][0];
    double y_2 = arr_node[arr_triangle_i[1]][1];
    double x_3 = arr_node[arr_triangle_i[2]][0];
    double y_3 = arr_node[arr_triangle_i[2]][1];

    return 0.5 * fabs(x_1 * (y_2 - y_3) + x_2 * (y_3 - y_1) + x_3 * (y_1 - y_2));
}

double middle(int* arr_triangle_i, double** arr_node){
    double x_1 = arr_node[arr_triangle_i[0]][0];
    double y_1 = arr_node[arr_triangle_i[0]][1];
    double x_2 = arr_node[arr_triangle_i[1]][0];
    double y_2 = arr_node[arr_triangle_i[1]][1];
    double x_3 = arr_node[arr_triangle_i[2]][0];
    double y_3 = arr_node[arr_triangle_i[2]][1];

    double x_1_res = (x_1 + x_2) / 2.0;
    double y_1_res = (y_1 + y_2) / 2.0;
    double x_2_res = (x_1 + x_3) / 2.0;
    double y_2_res = (y_1 + y_3) / 2.0;
    double x_3_res = (x_2 + x_3) / 2.0;
    double y_3_res = (y_2 + y_3) / 2.0;

    return f(x_1_res, y_1_res) + f(x_2_res, y_2_res) + f(x_3_res, y_3_res);
}

void fun1(std::ifstream& file, int& N_node, int& N_triangle, int& N_inside, int& N_outside){
    file >> N_node;
    file >> N_triangle;
    file >> N_inside;
    file >> N_outside;

    std::string line;

    for (int i = 0; i < 3; ++i) {
        std::getline(file, line);
    }
}

void fun2(std::ifstream& file, int N_node, double** arr_node){
    int index;
    for (int i = 0; i < N_node; i++){
        file >> index >> arr_node[i][0] >> arr_node[i][1];
    }

    std::string line;

    for (int i = 0; i < 3; ++i) {
        std::getline(file, line);
    
    }
}

void fun3(std::ifstream& file, int N_triangle, int** arr_triangle){
    int index;
    for (int i = 0; i < N_triangle; i++){
        file >> index >> arr_triangle[i][0] >> arr_triangle[i][1] >> arr_triangle[i][2];
    }

    std::string line;

    for (int i = 0; i < 3; ++i) {
        std::getline(file, line);
    
    }
}

void fun4(std::ifstream& file, int N_node, int** arr_node){
    int index;
    for (int i = 0; i < N_node; i++){
        file >> index >> arr_node[i][0] >> arr_node[i][1];
    }

    std::string line;

    for (int i = 0; i < 3; ++i) {
        std::getline(file, line);
    
    }
}

void print_arr(int N, int** arr){
    for (int i = 0; i < N; i++){
        printf("%d %d %d\n", arr[i][0], arr[i][1], arr[i][2]);
    }
}

int main(){

    std::ifstream file("file6.txt");

    int N_node, N_triangle, N_inside, N_outside;

    fun1(file, N_node, N_triangle, N_inside, N_outside);

    double** arr_node = (double**)malloc(N_node * sizeof(double*));
    for (int i = 0; i < N_node; i++){
        arr_node[i] = (double*)calloc(2, sizeof(double));
    }

    int** arr_triangle = (int**)malloc(N_triangle * sizeof(int*));
    for (int i = 0; i < N_triangle; i++){
        arr_triangle[i] = (int*)calloc(3, sizeof(int));
    }

    int** arr_inside = (int**)malloc(N_inside * sizeof(int*));
    for (int i = 0; i < N_inside; i++){
        arr_inside[i] = (int*)calloc(2, sizeof(int));
    }

    int** arr_outside = (int**)malloc(N_outside * sizeof(int*));
    for (int i = 0; i < N_outside; i++){
        arr_outside[i] = (int*)calloc(2, sizeof(int));
    }

    fun2(file, N_node, arr_node);
    fun3(file, N_triangle, arr_triangle);
    fun4(file, N_inside, arr_inside);
    fun4(file, N_outside, arr_outside);

    double res = 0.0;

    for (int i = 0; i < N_triangle; i++){
        res += 1.0 / 3.0 * square(arr_triangle[i], arr_node) * middle(arr_triangle[i], arr_node);
    }

    printf("%lf\n", fabs(res - 23.0 / 45.0));

    //printf("%lf\n", log(fabs(res - 23.0 / 45.0)));

    for (int i = 0; i < N_node; i++){
        free(arr_node[i]);
    }
    free(arr_node);
    for (int i = 0; i < N_triangle; i++){
        free(arr_triangle[i]);
    }
    free(arr_triangle);
    for (int i = 0; i < N_inside; i++){
        free(arr_inside[i]);
    }
    free(arr_inside);
    for (int i = 0; i < N_outside; i++){
        free(arr_outside[i]);
    }
    free(arr_outside);

    file.close();
    return 0;
}
