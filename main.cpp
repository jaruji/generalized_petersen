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

bool edgeIsValid(int v, bool **matrix, int path[], int pos)
{
    if (matrix[path[pos-1]][v] == 0)
        return 0;
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;
    return 1;
}

/* solve hamiltonian cycle problem */
int findHamCycle(bool **matrix, int path[], int pos, int n)
{
    int sum = 0;
    if (pos == n)
    {
        if (matrix[ path[pos-1] ][ path[0] ] == 1) {
//            printf("Nasla sa cesta:\n");
//            for(int k = 0; k < n; k++)
//                printf("%d ", path[k]);
//            printf("\n\n");
            return 1;
        }
        else
            return 0;
    }

    for (int i = 1; i < n; i++)
    {
        if (edgeIsValid(i, matrix, path, pos))
        {
            path[pos] = i;
            sum += findHamCycle(matrix, path, pos+1, n);
            path[pos] = -1;
        }
    }
    return sum;
}

/* solves the Hamiltonian Cycle problem using Backtracking.*/
int numOfHamCycles(bool **matrix, int n)
{
    int *path = new int[n];
    for (int i = 0; i < n; i++)
        path[i] = -1;
    path[0] = 0;
    return findHamCycle(matrix, path, 1, n);
}

bool **setFixedMatrixPart(bool **matrix, int n){
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

bool **setInnerMatrixPart(bool **matrix, int n, int r){
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

bool **generateMatrix(int n, int r){
    const auto N = 2*n;
    bool **matrix = new bool*[N]();
    for(int i = 0; i < N; ++i) {
        matrix[i] = new bool[N]();
    }
    matrix = setFixedMatrixPart(matrix, n);
    matrix = setInnerMatrixPart(matrix, n, r);
    return matrix;
}

void printMatrix(bool **matrix, int n){
    for(int i = 0; i < 2 * n; i++){
        for(int j = 0; j < 2 * n; j++){
            std::cout << matrix[i][j] ;
        }
        std::cout << '\n';
    }
}

int main(){
    int n = 3, cycles = 0;
    while(n <= 40) {
        int r = 1;
        while(r < (int)ceil((double)n / 2.0)) {
            std::cout << "n: " << n << ", r: " << r << '\n';
            auto matrix = generateMatrix(n, r);
//            printMatrix(matrix, n);
            cycles = numOfHamCycles(matrix, 2*n);
            if(cycles == 0)
                printf("Nema ziadne kruznice\n");
            else
                printf("Naslo sa %d kruznic\n", cycles/2);
            for (int i = 0; i < 2 * n; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
            r++;
        }
        std::cout << "################################################\n";
        n++;
    }
}