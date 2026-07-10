#include <iostream> 
#include <cstdlib> 
#include <cmath>  
#include <fstream>
#include <ctime>
#include <algorithm>
#include <chrono>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double** create_matrix(int N_x, int N_y){

    double** W = (double**)malloc(N_y * sizeof(double*));
    for (int i = 0; i < N_y; i++) {
        W[i] = (double*)calloc(N_x, sizeof(double));
    }

    return W;
}

void free_matrix(double** W, int N_x, int N_y){
    (void) N_x;
    for (int i = 0; i < N_y; i++) free(W[i]);
    free(W);
}

void transposed(double** A, double** A_transposed, int N_x, int N_y, int M){
    for (int i = 0; i < N_x * N_y; i++){
        for (int j = 0; j < M * M; j++){
            A_transposed[i][j] = A[j][i];
        }
    }
}

void product(double** A_transposed, double** A, double** C, int N_x, int N_y, int M){

    for (int i = 0; i < N_x * N_y; i++) {
        for (int j = 0; j < N_x * N_y; j++) {
            for (int k = 0; k < M * M; k++) {
                C[i][j] += A_transposed[i][k] * A[k][j];
            }
        }
    }

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

void print_arr(int N, double* arr){
    for (int i = 0; i < N; i++) printf("%lf\n", arr[i]);
}

void print_matrix(double** W, int N_x, int N_y){

    for (int i = 0; i < N_y; i++){
        for(int j = 0; j < N_x; j++){
                printf("%lf ", W[i][j]);
        }

        printf("\n");
    }

    printf("\n\n");
    printf("---");
    printf("\n\n");
}

double u(double x, double y){
    return x * x * (x - 0.5) * (x - 0.5) * y * y * (y - 0.5) * (y - 0.5);
}

void fun(double** points, int M){

    double x_1 = 0.0;
    double y_1 = 0.0;

    double x_2 = 0.0;
    double y_2 = 1.0;

    double x_3 = 1.0;
    double y_3 = 0.0;

    double x_4 = 1.0;
    double y_4 = 1.0;

    double h = (x_3 - x_2) / (M - 1);

    double y_i = y_2;

    for(int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            points[j + i * M][0] = x_2 + h * j;
            points[j + i * M][1] = y_i;
        }
        y_i -= h;
    }
}

double square(double x1, double y1, double x2, double y2, double x3, double y3){
    return 0.5 * fabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
}

int find_triangle(int** arr_triangle, double** arr_node, int N_triangle, double x, double y){

    for (int i = 0; i < N_triangle; i++){

        double x1 = arr_node[arr_triangle[i][0]][0];
        double y1 = arr_node[arr_triangle[i][0]][1];

        double x2 = arr_node[arr_triangle[i][1]][0];
        double y2 = arr_node[arr_triangle[i][1]][1];

        double x3 = arr_node[arr_triangle[i][2]][0];
        double y3 = arr_node[arr_triangle[i][2]][1];

        double S_true = square(x1, y1, x2, y2, x3, y3);
        double S = square(x1, y1, x2, y2, x, y) + square(x1, y1, x, y, x3, y3) + square(x, y, x2, y2, x3, y3);

        if (fabs(S - S_true) < 1e-12){
            return i;
        }

    }

    return -1;

}

double ksi_n1(double x, double y, int n2, int n3, double** arr_node){
    double x2 = arr_node[n2][0];
    double y2 = arr_node[n2][1];

    double x3 = arr_node[n3][0];
    double y3 = arr_node[n3][1];

    return (x - x2) * (y3 - y2) - (y - y2) * (x3 - x2);
}

double ksi_n2(double x, double y, int n1, int n3, double** arr_node){
    double x1 = arr_node[n1][0];
    double y1 = arr_node[n1][1];

    double x3 = arr_node[n3][0];
    double y3 = arr_node[n3][1];

    return (x - x1) * (y3 - y1) - (y - y1) * (x3 - x1);
}

double ksi_n3(double x, double y, int n1, int n2, double** arr_node){
    double x1 = arr_node[n1][0];
    double y1 = arr_node[n1][1];

    double x2 = arr_node[n2][0];
    double y2 = arr_node[n2][1];

    return (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);

}

void fun_phi(int n_triangle, double** phi, double** arr_node, int** arr_triangle, int N_x, int N_y, double x, double y){

    int n1 = arr_triangle[n_triangle][0];
    int n2 = arr_triangle[n_triangle][1];
    int n3 = arr_triangle[n_triangle][2];

    for (int i = 0; i < N_y; i++){
        for (int j = 0; j < N_x; j++){

            if (i + j * N_y == n1){
                phi[i][j] = ksi_n1(x, y, n2, n3, arr_node) / ksi_n1(arr_node[n1][0], arr_node[n1][1], n2, n3, arr_node);
            }

            else if (i + j * N_y == n2){
                phi[i][j] = ksi_n2(x, y, n1, n3, arr_node) / ksi_n2(arr_node[n2][0], arr_node[n2][1], n1, n3, arr_node);
            }

            else if (i + j * N_y == n3){
                phi[i][j] = ksi_n3(x, y, n1, n2, arr_node) / ksi_n3(arr_node[n3][0], arr_node[n3][1], n1, n2, arr_node);
            }

            else{
                phi[i][j] = 0.0;
            }
        }
    }
}

void method(double* x, int N, double** W){

    // прямой ход

    for (int i = 0; i < N - 1; i++){

        int max_row = i;
        for(int j = i + 1; j < N; j++){
            if (fabs(W[j][i]) >= fabs(W[max_row][i])){
                max_row = j;
            }
        }

        std::swap(W[i], W[max_row]);

        double flag1 = W[i][i];
        for (int j = i; j < N + 1; j++){
            W[i][j] /= flag1;
        }


        for (int j = i + 1; j < N; j++){
            double flag2 = W[j][i];
            for(int k = i; k < N + 1; k++){
                W[j][k] -= W[i][k] * flag2;
            }
        }

    }

    // обратный ход

    x[N - 1] = W[N - 1][N] / W[N - 1][N - 1];

    for (int i = N - 2; i >= 0; i--){
        x[i] = W[i][N];

        for (int j = N - 1; j >= i + 1; j--){
            x[i] -= x[j] * W[i][j];
        }

        x[i] /= W[i][i];
    }

    //print_array(x, N);
}

void made_A(double** A, int N_x, int N_y, int M, int N_triangle, double** arr_node, int** arr_triangle, double** points){

    double** phi = create_matrix(N_x, N_y); 

    for (int i = 0; i < M * M; i++){
        int n_triangle = find_triangle(arr_triangle, arr_node, N_triangle, points[i][0], points[i][1]);

        fun_phi(n_triangle, phi, arr_node, arr_triangle, N_x, N_y, points[i][0], points[i][1]);

        for (int x = 0; x < N_x; x++) {
            for (int y = 0; y < N_y; y++) {
                A[i][x * N_y + y] = phi[x][y];
        
            }
        }
    }
    free_matrix(phi, N_x, N_y);
}

void fun_c(double** c, double** points, int N_x, int N_y, int M, int N_triangle, double** arr_node, int** arr_triangle, double** A){
    double** A_transposed = create_matrix(M * M, N_x * N_y);
    double** C = create_matrix(N_x * N_y, N_x * N_y);
    double* b = (double*)calloc(M * M, sizeof(double));
    double* c_method = (double*)calloc(N_x * N_y, sizeof(double));
    double* B = (double*)calloc(N_x * N_y, sizeof(double));
    double** W = create_matrix(N_x * N_y + 1, N_x * N_y);

    made_A(A, N_x, N_y, M, N_triangle, arr_node, arr_triangle, points);
    transposed(A, A_transposed, N_x, N_y, M);
    product(A_transposed, A, C, N_x, N_y, M);

    for (int i = 0; i < M * M; i++){
        b[i] = u(points[i][0], points[i][1]);
    }

    for (int i = 0; i < N_x * N_y; i++){
        for (int k = 0; k < M * M; k++){
            B[i] += A_transposed[i][k] * b[k];
        }
    }

    for (int i = 0; i < N_x * N_y; i++){
        for (int j = 0; j < N_x * N_y; j++){
            W[i][j] = C[i][j];
        }
    }

    for (int i = 0; i < N_x * N_y; i++) W[i][N_x * N_y] = B[i];

    method(c_method, N_x * N_y, W);

    for (int x = 0; x < N_x; x++){
        for (int y = 0; y < N_y; y++){
            c[x][y] = c_method[x * N_y + y];
        }
    }


    free_matrix(A_transposed, M * M, N_x * N_y);
    free_matrix(C, N_x * N_y, N_x * N_y);
    free_matrix(W, N_x * N_y + 1, N_x * N_y);
    free(b);
    free(c_method);
    free(B);
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

    std::ofstream file_res("file8_2.txt");

    int N_x = 32;
    int N_y = 32;

    int M = N_x * 2;

    N_x += 1;
    N_y += 1;

    M += 1;

    double** points = (double**)malloc(M * M * sizeof(double*));
    for (int i = 0; i < M * M; i++){
        points[i] = (double*)calloc(2, sizeof(double));
    }

    fun(points, M);

    double** A = create_matrix(N_x * N_y, M * M);

    double** phi = create_matrix(N_x, N_y); 
    double** c = create_matrix(N_x, N_y);
    fun_c(c, points, N_x, N_y, M, N_triangle, arr_node, arr_triangle, A);

    double delta = 0.0;

    for (int i = 0; i < M * M; i++){

        for (int x = 0; x < N_x; x++) {
            for (int y = 0; y < N_y; y++) {
                phi[x][y] = A[i][x * N_y + y];
        
            }
        }

        double res = 0.0;

        for (int i = 0; i < N_y; i++){
            for (int j = 0; j < N_x; j++){
                res += c[i][j] * phi[i][j];
            }
        }

        if (fabs(res - u(points[i][0], points[i][1])) > delta){
            delta = fabs(res - u(points[i][0], points[i][1]));
        }

        file_res << points[i][0] << " " << points[i][1] << " " << u(points[i][0], points[i][1]) << " " << res << " " << fabs(res - u(points[i][0], points[i][1])) << "\n";

    }

    printf("%lf\n", delta);

    for (int i = 0; i < N_node; i++) free(arr_node[i]);
    free(arr_node);
    for (int i = 0; i < N_triangle; i++) free(arr_triangle[i]);
    free(arr_triangle);
    for (int i = 0; i < N_inside; i++) free(arr_inside[i]);
    free(arr_inside);
    for (int i = 0; i < N_outside; i++) free(arr_outside[i]);
    free(arr_outside);
    free_matrix(A, N_x * N_y, M * M);
    for (int i = 0; i < N_y; i++)free(c[i]);
    free(c);
    for (int i = 0; i < N_y; i++) free(phi[i]);
    free(phi);
    for (int i = 0; i < M * M; i++) free(points[i]);
    free(points);

    file.close();
    file_res.close();

    return 0;
}
