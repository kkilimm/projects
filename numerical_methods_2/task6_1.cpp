#include <iostream> 
#include <cstdlib> 
#include <cmath>  
#include <fstream>
#include <ctime>
#include <algorithm>
#ifndef PI
    #define PI 3.14159265358979323846
#endif

void fun(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, double x_4, double y_4, int N_x, int N_y, std::ofstream& file){

    file << (N_x + 1) * (N_y + 1) << "\n"; //число вершин

    file << N_x * N_y * 2 << "\n"; // число треугольников 

    file << (3 * (N_x - 1) + 2) * (N_y - 1) + (2 * (N_x - 1) + 1) << "\n"; // число внутренних ребер 

    file << 2*N_x + 2*N_y << "\n"; // число граничных ребер 



    file << "\n" << "----------" << "\n" << "\n";



    double h_x = (x_3 - x_2) / N_x;
    double h_y = (y_2 - y_1) / N_y;

    double x_i = x_2;

    for(int i = 0; i < N_x + 1; i++){

        for (int j = 0; j < N_y + 1; j++){

            file << (N_y + 1) * i + j << "   " << x_i << " " << y_2 - h_y * j << "\n";
        }

        x_i += h_x;
    }



    file << "\n" << "----------" << "\n" << "\n";



    int k = 0;

    for (int i = 0; i < N_x; i++){

        for (int j = 0; j < N_y; j++){

            file << k << "   " << (N_y + 1) * i + j << " " << (N_y + 1) * i + j + 1 << " " << (N_y + 1) * i + j + N_y + 2 << "\n";

            file << k + 1 << "   " << (N_y + 1) * i + j << " " << (N_y + 1) * i + j + N_y + 2 << " " << (N_y + 1) * i + j + N_y + 1 << "\n";

            k += 2;

        }
    }



    file << "\n" << "----------" << "\n" << "\n";



    k = 0;

    for (int i = 0; i < N_x; i++){

        for (int j = 0; j < N_y; j++){

            if (i == N_x - 1 & j == N_y - 1){

                file << k << "   " << j + (N_y + 1) * i << " " << j + 1 + (N_y + 1) * (i + 1) << "\n";

                k += 1;
            }

            else if (i == N_x - 1){

                file << k << "   " << j + 1 + (N_y + 1) * i << " " << j + 1 + (N_y + 1) * (i + 1) << "\n";

                file << k + 1 << "   " << j + (N_y + 1) * i << " " << j + 1 + (N_y + 1) * (i + 1) << "\n";

                k += 2;
            }

            else if (j == N_y - 1){

                file << k << "   " << j + (N_y + 1) * i << " " << j + 1 + (N_y + 1) * (i + 1) << "\n";

                file << k + 1 << "   " << j + (N_y + 1) * (i + 1) << " " << j + 1 + (N_y + 1) * (i + 1) << "\n";

                k += 2;
            }

            else{

                file << k << "   " << j + 1 + (N_y + 1) * i << " " << j + 1 + (N_y + 1) * (i + 1) << "\n";

                file << k + 1 << "   " << j + (N_y + 1) * i << " " << j + 1 + (N_y + 1) * (i + 1) << "\n";

                file << k + 2 << "   " << j + (N_y + 1) * (i + 1) << " " << j + 1 + (N_y + 1) * (i + 1) << "\n";

                k += 3;
            }
        }

    }



    file << "\n" << "----------" << "\n" << "\n";



    for (int i = 0; i < N_y; i++){

        file << i << "   " << i << " " << i + 1 << "\n";
    }

    for (int i = 0; i < N_x; i++){

        file << i + N_y  << "   " << N_y + i * (N_y + 1) << " " << N_y + (i + 1) * (N_y + 1) << "\n";
    }

    for (int i = 0; i < N_y; i++){

        file << i + N_y + N_x << "   " << (N_x + 1) * (N_y + 1) - 1 - i  << " " << (N_x + 1) * (N_y + 1) - 2 - i << "\n";
    }

    for (int i = 0; i < N_x; i++){

        file << i + N_y + N_x + N_y << "   " << (N_x + 1) * (N_y + 1) - (N_y + 1) * (i + 1) << " " << (N_x + 1) * (N_y + 1) - (N_y + 1) * (i + 2) << "\n";
    }


}


int main(){

    int N_x = 16;
    int N_y = 16;

    double x_1 = 0.0;
    double y_1 = 0.0;

    double x_2 = 0.0;
    double y_2 = 1.0;

    double x_3 = 1.0;
    double y_3 = 1.0;

    double x_4 = 1.0;
    double y_4 = 0.0;

    std::ofstream file("file6.txt");

    fun(x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, N_x, N_y, file);

    printf("%lf\n", log(1.0 / N_x));

    return 0;
}