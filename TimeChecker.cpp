#include <eigen3/Eigen/Dense>
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

    int matrixNum = atoi(argv[1]);

    std::cout << "size " << matrixNum << std::endl;

    Eigen::MatrixXd eigenMat1 = Eigen::MatrixXd::Random(matrixNum, matrixNum);
    Eigen::MatrixXd eigenMat2 = Eigen::MatrixXd::Random(matrixNum, matrixNum);
    Eigen::MatrixXd plusEigenMat = Eigen::MatrixXd::Random(matrixNum, matrixNum);
    Eigen::MatrixXd multEigenMat = Eigen::MatrixXd::Random(matrixNum, matrixNum);

    std::vector<int> cells;
    for (int i = 0; i < matrixNum * matrixNum; ++i)
    {
        cells.push_back(1);
    }

    Matrix<int> libMat(matrixNum, matrixNum, cells);
    Matrix<int> plusMat(matrixNum, matrixNum);
    Matrix<int> multMat(matrixNum, matrixNum);

    std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;
    std::chrono::duration<double> elapsed_seconds;

    // Mult eigen Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    multEigenMat = eigenMat1 * eigenMat2;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << "eigen mult " << elapsed_seconds.count() << std::endl;
    tictoc_stack.pop();

    // Plus eigen Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    plusEigenMat = eigenMat1 + eigenMat2;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << "eigen add " << elapsed_seconds.count() << std::endl;
    tictoc_stack.pop();

    // Multiplication lib Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    multMat = libMat * libMat;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << "matlib mult " << elapsed_seconds.count() << std::endl;
    tictoc_stack.pop();

    // Plus lib Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    plusMat = libMat + libMat;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << "matlib add " << elapsed_seconds.count() << std::endl;
    tictoc_stack.pop();
}
