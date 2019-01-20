#ifndef EX3_CPP_MATRIX_H
#define EX3_CPP_MATRIX_H

#include <iostream>
#include <vector>
#include <iterator>
#include "Complex.h"

template <class T>
class Matrix
{
public:
    typedef typename std::vector<T>::const_iterator const_iterator;

    Matrix() : Matrix(1, 1)
    {
    }

    Matrix(unsigned int rows, unsigned int cols)// : Matrix(rows, cols, std::vector<T>{0})
    {
        _rows = rows;
        _cols = cols;

        for (int i = 0; i < _rows*_cols; ++i)
        {
            _matrix.push_back(0);
        }
    }

    Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells)
    {
        _rows = rows;
        _cols = cols;

        for (int i = 0; i < cells.size(); ++i)
        {
            _matrix.push_back(cells[i]);
        }
    }

    Matrix(const Matrix<T>& other)
    {
        _rows = other._rows;
        _cols = other._cols;

        for (int i = 0; i < _rows*_cols; ++i)
        {
            _matrix.push_back(other._matrix[i]);
        }
    }

    ~Matrix() = default;

    const_iterator begin() const
    {
        return _matrix.cbegin();
    }

    const_iterator end() const
    {
        return _matrix.cend();
    }

    Matrix<T>& operator=(const Matrix<T>& rhs)
    {
        _rows = rhs._rows;
        _cols = rhs._cols;
        for (int i = 0; i < _rows*_cols; ++i)
        {
            _matrix[i] = rhs._matrix[i];
        }
        return *this;
    }

    Matrix<T> operator+(const Matrix<T>& rhs) const
    {
        if (rows() != rhs.rows() || cols() != rhs.cols())
        {
            throw "Matrices have to be the same dimensions!";
        }

        Matrix<T> res(rows(), cols());
        for (int i = 0; i < rows()*cols(); ++i)
        {
            res._matrix[i] = _matrix[i] + rhs._matrix[i];
        }
        return res;
    }

    Matrix<T> operator-(const Matrix<T>& rhs) const
    {
        if (rows() != rhs.rows() || cols() != rhs.cols())
        {
            throw "Matrices have to be the same dimensions!";
        }

        Matrix<T> res(rows(), cols());
        for (int i = 0; i < rows()*cols(); ++i)
        {
            res._matrix[i] = _matrix[i] - rhs._matrix[i];
        }
        return res;
    }

    Matrix<T> operator*(const Matrix<T>& rhs) const
    {
        if (cols() != rhs.rows())
        {
            throw "# columns left matrix != # rows right matrix";
        }

        Matrix<T> res(this->rows(), rhs.cols());
        Matrix<T> mat = *this;

        for (int cell = 0; cell < res._matrix.size(); ++cell)
        {
            int row = cell / res.cols();
            int col = cell % res.cols();

            for (int i = 0; i < this->rows(); ++i)
            {
                res._matrix[cell] += this->_matrix[row*this->cols()+i] *
                            rhs._matrix[col+i*rhs.cols()];
            }
        }
        return res;
    }

    bool operator==(const Matrix<T>& rhs) const
    {
        for (int i = 0; i < rows()*cols(); ++i)
        {
            if (_matrix[i] != rhs._matrix[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix<T>& rhs) const
    {
        return (! *this == rhs);
    }

    T& operator()(unsigned int row, unsigned int col)
    {
        return _matrix[row*rows() + col];
    }

    T operator()(unsigned int row, unsigned int col) const
    {
        return _matrix[row*rows() + col];
    }

    Matrix trans() const;

    bool isSquareMatrix() const
    {
        return rows() == cols();
    }

    friend std::ostream& operator<<(std::ostream& output, const Matrix<T>& mat)
    {
        for (int i = 0; i < mat.rows(); ++i)
        {
            for (int j = 0; j < mat.cols(); ++j)
            {
                output << mat(i, j) << '\t';
            }
            output << '\n';
        }
        return output;
    }

    unsigned int rows() const
    {
        return _rows;
    }

    unsigned int cols() const
    {
        return _cols;
    }

private:
    std::vector<T> _matrix;
    unsigned int _rows;
    unsigned int _cols;
};

template <typename T>
Matrix<T> Matrix<T>::trans() const
{
    if (! isSquareMatrix())
    {
        throw "Matrix is not square!";
    }

    Matrix<T> res(cols(), rows());
    Matrix<T> mat = *this;

    for (int i = 0; i < cols(); ++i)
    {
        for (int j = 0; j < rows(); ++j)
        {
            res(i, j) = mat(j, i);
        }
    }
    return res;
}

template <>
Matrix<Complex> Matrix<Complex>::trans() const
{
    Matrix<Complex> res(cols(), rows());
    Matrix<Complex> mat = *this;

    for (unsigned int i = 0; i < cols(); ++i)
    {
        for (unsigned int j = 0; j < rows(); ++j)
        {
            res(i, j) = mat(j, i).conj();
        }
    }
    return res;
}

#endif //EX3_CPP_MATRIX_H