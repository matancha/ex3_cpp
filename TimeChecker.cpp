#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <chrono>

#include "Matrix.hpp"
#define MATRIX_SIZE_ARG_INDEX 1

const char* USAGE_MSG = "Usage: TimeChecker <matrix_num>";
const char* SIZE_MSG = "size ";
const int NUM_ARGUMENTS = 1;
const char* EIGEN_MULT_MSG = "eigen mult ";
const char* EIGEN_ADD_MSG = "eigen add ";
const char* MATLIB_MULT_MSG = "matlib mult ";
const char* MATLIB_ADD_MSG = "eigen add ";
const int USER_DEFINED_MATRIX_NUMBER = 1;

/**
 * Checks running time - comparing eigen and matlib
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    if (argc != NUM_ARGUMENTS + 1)
    {
        std::cerr << USAGE_MSG << std::endl;
        exit(EXIT_FAILURE)
    }

    int n = atoi(argv[MATRIX_SIZE_ARG_INDEX]);

    std::cout << SIZE_MSG << n << std::endl;

    Eigen::MatrixXd eigenMat1 = Eigen::MatrixXd::Random(n, n);
    Eigen::MatrixXd eigenMat2 = Eigen::MatrixXd::Random(n, n);
    Eigen::MatrixXd plusEigenMat;
    Eigen::MatrixXd multEigenMat;

    std::vector<int> cells(n * n);
    for (int i = 0; i < n * n; ++i)
    {
        cells[i] = USER_DEFINED_MATRIX_NUMBER;
    }

    Matrix<int> libMat(n, n, cells);
    Matrix<int> plusMat(n, n);
    Matrix<int> multMat(n, n);

    std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;
    std::chrono::duration<double> elapsed_seconds;

    // Mult eigen Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    multEigenMat = eigenMat1 * eigenMat2;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << EIGEN_MULT_MSG << elapsed_seconds.count() << std::endl;
    tictoc_stack.pop();

    // Plus eigen Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    plusEigenMat = eigenMat1 + eigenMat2;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << EIGEN_ADD_MSG << elapsed_seconds.count() << std::endl;
    tictoc_stack.pop();

    // Multiplication lib Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    multMat = libMat * libMat;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << MATLIB_MULT_MSG << elapsed_seconds.count() << std::endl;
    tictoc_stack.pop();

    // Plus lib Matrix
    tictoc_stack.push(std::chrono::system_clock::now());
    plusMat = libMat + libMat;
    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << MATLIB_ADD_MSG << elapsed_seconds.count() << std::endl;
    tictoc_stack.pop();
}
