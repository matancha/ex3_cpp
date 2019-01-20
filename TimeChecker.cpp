//#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <chrono>

#include "Matrix.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: TimeChecker <matrix_num>" << std::endl;
    }

    unsigned int matrixNum = atoi(argv[1]);
//  MatrixXd eigenMat1 = MatrixXd::Random(matrixNum, matrixNum);
//  MatrixXd eigenMat2 = MatrixXd::Random(matrixNum, matrixNum);

    std::vector<int> cells;
    for (int i = 0; i < matrixNum * matrixNum; ++i)
    {
        cells.push_back(1);
    }

    Matrix<int> libMat(matrixNum, matrixNum, cells);
    Matrix<int> plusMat(matrixNum, matrixNum);
    std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;
    std::chrono::duration<double> elapsed_seconds;

    // Plus lib Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    plusMat = libMat + libMat;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << "Time elapsed: " << elapsed_seconds.count() << "sec\n";
    tictoc_stack.pop();

    // Multiplication lib Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    plusMat = libMat * libMat;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << "Time elapsed: " << elapsed_seconds.count() << "sec\n";
    tictoc_stack.pop();
}
