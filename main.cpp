#include <iostream>
#include <cstdlib>
#include <array>
#include <numeric>
#include "vector"
#include <cmath>

/*
Zadanie cislo 2 z GRA_I:
Vyhladavanie hamiltonovskych cyklov v generalizovanych Petersonovych grafoch
*/

int **setFixedMatrixPart(int **matrix, int n){
    for(int i = 0; i < n; i++){
        matrix[i][(i + 1) % n] = 1;
        if(i - 1 < 0){
            matrix[i][n + (i - 1) % n] = 1;
        }
        else {
            matrix[i][(i - 1) % n] = 1;
        }
        matrix[i][i + n] = 1;
        matrix[i + n][i] = 1;
    }
    return matrix;
}

int **setInnerPart(int **matrix, int n, int r){
    for(int i = n; i < 2*n; i++){
        matrix[i][n + (i + r) % n] = 1;
        if(i - 1 < 0){
            matrix[i][n + n + (i - r) % n] = 1;
        }
        else {
            matrix[i][n + (i - r) % n] = 1;
        }
    }
    return matrix;
}

int **generateMatrix(int n, int r){
    const auto N = 2*n;
    int **matrix = new int*[N]();
    for(int i = 0; i < N; ++i) {
        matrix[i] = new int[N]();
    }
    matrix = setFixedMatrixPart(matrix, n);
    matrix = setInnerPart(matrix, n, r);
    return matrix;
}

int findHamiltonianCycles(int **matrix, int n){
    return 0;
}

void printMatrix(int **matrix, int n){
    for(int i = 0; i < 2 * n; i++){
        for(int j = 0; j < 2 * n; j++){
            std::cout << matrix[i][j] ;
        }
        std::cout << '\n';
    }
}

int main(){
    int n = 3;
    while(n <= 12) {
        int r = 1;
        while(r < (int)ceil((double)n / 2.0)) {
            std::cout << "n: " << n << ", r: " << r << '\n';
            auto matrix = generateMatrix(n, r);
            printMatrix(matrix, n);
            findHamiltonianCycles(matrix, n);
            for (int i = 0; i < 2 * n; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
            r++;
        }
        std::cout << "\n################################################\n";
        n++;
    }
}