#include <eigen3/Eigen/Dense>
#include <iostream>
#include "Matrix.hpp"

int main(int argc, char *argv[])
{
  if (argc != 1)
  {
    throw "Usage: TimeChecker <number>"
  }

  int matrixNum = argv[1]
  MatrixXd eigenMat = MatrixXd::Random(matrixNum, matrixNum);
  Matrix<int> libMat = Matrix();
}
