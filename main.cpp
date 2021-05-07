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


//=================================================================

/* algo from https://www.sanfoundry.com/cpp-program-find-hamiltonian-cycle/ */
//void printSolution(int path[], int n)
//{
//    std::cout<<"Solution Exists: ";
//    for (int i = 0; i < n; i++)
//        std::cout<<path[i]<<"  ";
//    std::cout<< path[0]<<std::endl;
//}
//
//bool isSafe(int v, bool **graph, int path[], int pos)
//{
//    if (graph [path[pos-1]][v] == 0)
//        return false;
//    for (int i = 0; i < pos; i++)
//        if (path[i] == v)
//            return false;
//    return true;
//}
//
///* solve hamiltonian cycle problem */
//bool hamCycleUtil(bool **graph, int path[], int pos, int n)
//{
//    if (pos == n)
//    {
//        if (graph[ path[pos-1] ][ path[0] ] == 1)
//            return true;
//        else
//            return false;
//    }
//
//    for (int v = 1; v < n; v++)
//    {
//        if (isSafe(v, graph, path, pos))
//        {
//            path[pos] = v;
//            if (hamCycleUtil (graph, path, pos+1, n) == true)
//                return true;
//            path[pos] = -1;
//        }
//    }
//    return false;
//}
//
///* solves the Hamiltonian Cycle problem using Backtracking.*/
//bool hamCycle(bool **graph, int n)
//{
//    int *path = new int[n];
//    for (int i = 0; i < n; i++)
//        path[i] = -1;
//    path[0] = 0;
//    if (hamCycleUtil(graph, path, 1, n) == false)
//    {
//        std::cout<<"\nSolution does not exist"<<std::endl;
//        return false;
//    }
//    printSolution(path, n);
//    return true;
//}

//=================================================================

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

int findHamiltonianCycles(bool **matrix, int n){
    //hamCycle(matrix, 2*n);
    return 0;
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