#include <iostream>  
#include <cmath>   
#ifndef PI
    #define PI 3.14159265358979323846
#endif

double* create_lambdas(double h, int N) {

    double* lambdas = (double*)malloc((N - 1) * sizeof(double));
    for (int n = 0; n < N - 1; n++) {
        lambdas[n] = (4 / (h * h)) * sin((PI + 2 * PI * n) / (4 * N - 2)) * sin((PI + 2 * PI * n) / (4 * N - 2));
        printf("lambda_%d = %.20lf\n", n + 1, lambdas[n]);
    }
    return lambdas;
}

double* create_y_n(int n, int N, double C) {

    double* y_n = (double*)malloc((N - 1) * sizeof(double));
    for (int k = 0; k < N - 1; k++) {
        y_n[k] = C * sin((PI + 2 * PI * n) * (k + 1) / (2 * N - 1));
    }
    return y_n;

}

double** create_y(int N, double C) {

    double** y = (double**)malloc((N - 1) * sizeof(double*));
    for (int n = 0; n < N - 1; n++) {
        y[n] = create_y_n(n, N, C);
    }
    return y;
}

double** create_matrix(double h, int N) {

    double** matrix = (double**)malloc((N - 1) * sizeof(double*));
    for (int i = 0; i < N - 1; i++) {
        matrix[i] = (double*)calloc(N - 1, sizeof(double));
    }

    matrix[0][0] = -2.0 / (h * h);
    matrix[0][1] = 1.0 / (h * h);

    for (int i = 1; i < N - 2; i++) {
        matrix[i][i - 1] = 1.0 / (h * h);
        matrix[i][i] = -2.0 / (h * h);
        matrix[i][i + 1] = 1.0 / (h * h);
    }

    matrix[N - 2][N - 3] = 1.0 / (h * h);
    matrix[N - 2][N - 2] = -1.0 / (h * h);

    return matrix;
}

double scalar_product(double* y_n1, double* y_n2, int N) {

    double product = 0.0;
    for (int k = 0; k < N - 1; k++) {
        product += y_n1[k] * y_n2[k];
    }
    return product / (N-0.5);
}

void check_orthogonality(double** y, int N) {

    double product = 0.0;
    double max_product = 0.0;
    int max_n1 = 0;
    int max_n2 = 0;

    for (int n1 = 0; n1 < N - 1; n1++) {
        for (int n2 = n1; n2 < N - 1; n2++) {
            if (n1 != n2) {
                product = scalar_product(y[n1], y[n2], N);

                if (fabs(product) > fabs(max_product)) {
                    max_product = product;
                    max_n1 = n1;
                    max_n2 = n2;
                }

                printf("scalar product y_%d and y_%d = %.20e\n", n1 + 1, n2 + 1, product);
            }
        }
    }
    printf("most non-orthogonal vectors are y_%d and y_%d, max product = %.20e \n", max_n1 + 1, max_n2 + 1, max_product);
}

void find_vector(double** matrix, double* lambdas, double** y, int N) {

    double max_product = 0.0;
    int max_n = 0;
    double product = 0.0;
    double* Ay = (double*)calloc((N - 1), sizeof(double));
    double ch = 0.0;
    double zm = 0.0;

    for (int n = 0; n < N - 1; n++) {

        for (int i = 0; i < N - 1; i++) {
            for (int j = 0; j < N - 1; j++) {
                Ay[i] += matrix[i][j] * y[n][j];
            }
        }

        for (int k = 0; k < N - 1; k++) {
            ch += (Ay[k] + lambdas[n] * y[n][k]) * (Ay[k] + lambdas[n] * y[n][k]);
            zm += y[n][k] * lambdas[n] * y[n][k] * lambdas[n];
        }

        product = sqrt(ch / zm);

        if (product > max_product) {
            max_product = product;
            max_n = n;
        }

        printf("y_%d with = %.20e\n", n + 1, product);

        ch = 0.0;
        zm = 0.0;
        for (int q = 0; q < N - 1; q++) {
            Ay[q] = 0.0;
        }

    }
    printf("most vector is y_%d with = %.20e\n", max_n + 1, max_product);

    free(Ay);
}

int main() {

    int N = 10;
    double C = 1;
    double h = 1.0 / (N - 0.5);

    double* lambdas = create_lambdas(h, N);
    double** y = create_y(N, C);
    double** matrix = create_matrix(h, N);

    check_orthogonality(y, N);
    find_vector(matrix, lambdas, y, N);

    free(lambdas);
    for (int i = 0; i < N - 1; i++) {
        free(matrix[i]);
        free(y[i]);
    }
    free(matrix);
    free(y);

    return 0;
}
