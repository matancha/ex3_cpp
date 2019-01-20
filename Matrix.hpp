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

    /**
     * Default constructor
     */
    Matrix();

    /**
     * Zero cells constructor
     * @param rows
     * @param cols
     */
    Matrix(unsigned int rows, unsigned int cols);

    /**
     * Cells Constructor
     * @param rows
     * @param cols
     * @param cells
     */
    Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells);

    /**
     * Copy constructor
     * @param other
     */
    Matrix(const Matrix<T>& other);

    /**
     * Default destructor
     */
    ~Matrix() = default;

    /**
     * Matrix Iterator - begin
     * @return
     */
    const_iterator begin() const
    {
        return _matrix.begin();
    }

    /**
     * Matrix iterator - end
     * @return
     */
    const_iterator end() const
    {
        return _matrix.cend();
    }

    /**
     * Assignment operator
     * @param rhs
     * @return
     */
    Matrix<T>& operator=(const Matrix<T>& rhs);

    /**
     * Plus operator
     * @param rhs
     * @return
     */
    Matrix<T> operator+(const Matrix<T>& rhs) const;

    /**
     * Minus operator
     * @param rhs
     * @return
     */
    Matrix<T> operator-(const Matrix<T>& rhs) const;

    /**
     * Multiplication operator
     * @param rhs
     * @return
     */
    Matrix<T> operator*(const Matrix<T>& rhs) const;

    /**
     * Returns true if matrices are the same
     * @param rhs
     * @return
     */
    bool operator==(const Matrix<T>& rhs) const;

    /**
     * Returns true if matrices are different
     * @param rhs
     * @return
     */
    bool operator!=(const Matrix<T>& rhs) const;

    /**
     * Returns cell at point (row, col)
     * @param row
     * @param col
     * @return
     */
    T& operator()(unsigned int row, unsigned int col);

    /**
     * Returns cell at point (row, col)
     * @param row
     * @param col
     * @return
     */
    T operator()(unsigned int row, unsigned int col) const;

    /**
     * Returns transpose matrix
     * @param row
     * @param col
     * @return
     */
    Matrix trans() const;

    /**
     * Returns true if matrix is square
     * @return
     */
    bool isSquareMatrix() const;

    /**
     * Prints matrix
     * @param output
     * @param mat
     * @return
     */
    friend std::ostream& operator<<(std::ostream& output, const Matrix<T>& mat)
    {
        for (int i = 0; i < mat.rows(); ++i)
        {
            for (int j = 0; j < mat.cols(); ++j)
            {
                output << mat(i, j) << '\t';
            }
            output << std::endl;
        }
        return output;
    }

    /**
     * Returns # of rows
     * @return
     */
    unsigned int rows() const;

    /**
     * Returns # of cols
     * @return
     */
    unsigned int cols() const;
private:
    std::vector<T> _matrix;
    unsigned int _rows;
    unsigned int _cols;
};

template <typename T>
Matrix<T>::Matrix() : Matrix(1, 1)
{
}

template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols) : Matrix(rows, cols,
                                                                 std::vector<T>(rows * cols))
{
}

template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells)
{
    if (cells.size() != rows * cols)
    {
        throw std::invalid_argument("vector's size is not rows*cols");
    }

    if (rows <=0 || cols <= 0)
    {
        throw std::invalid_argument("rows and cols needs to be positive");
    }

    _rows = rows;
    _cols = cols;
    _matrix = std::vector<T>(_rows*_cols);

    for (unsigned int i = 0; i < _matrix.size(); ++i)
    {
        _matrix[i] = cells[i];
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
    _rows = other._rows;
    _cols = other._cols;
    _matrix = std::vector<T>(other._matrix.size());

    for (unsigned int i = 0; i < _matrix.size(); ++i)
    {
        _matrix[i] = other._matrix[i];
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
    _rows = rhs._rows;
    _cols = rhs._cols;
    _matrix = std::vector<T>(rhs._matrix.size());

    for (unsigned int i = 0; i < _matrix.size(); ++i)
    {
        _matrix[i] = rhs._matrix[i];
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) const
{
    if (rows() != rhs.rows() || cols() != rhs.cols())
    {
        throw std::invalid_argument("Matrices have to be the same dimensions!");
    }

    Matrix<T> res(rows(), cols());
    for (unsigned int i = 0; i < rows() * cols(); ++i)
    {
        res._matrix[i] = _matrix[i] + rhs._matrix[i];
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) const
{
    if (rows() != rhs.rows() || cols() != rhs.cols())
    {
        throw std::invalid_argument("Matrices have to be the same dimensions!");
    }

    Matrix<T> res(rows(), cols());
    for (unsigned int i = 0; i < rows() * cols(); ++i)
    {
        res._matrix[i] = _matrix[i] - rhs._matrix[i];
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) const
{
    if (cols() != rhs.rows())
    {
        throw std::invalid_argument("# columns left matrix != # rows right matrix");
    }

    Matrix<T> res(this->rows(), rhs.cols());
    Matrix<T> mat = *this;

    for (unsigned int cell = 0; cell < res._matrix.size(); ++cell)
    {
        int row = cell / res.cols();
        int col = cell % res.cols();

        T sum = 0;
        for (unsigned int i = 0; i < this->rows() - 1; ++i)
        {
            sum += mat(row, i) * rhs(i, col);
        }
        res._matrix[cell] = sum;
    }
    return res;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& rhs) const
{
    if (rows() != rhs.rows() || cols() != rhs.cols())
    {
        return false;
    }

    for (int i = 0; i < rows()*cols(); ++i)
    {
        if (_matrix[i] != rhs._matrix[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
T& Matrix<T>::operator()(unsigned int row, unsigned int col)
{
    if (row < 0 || row >= rows() || col < 0 || col >= cols())
    {
        throw std::invalid_argument("Out of bounds!");
    }

    return _matrix[row * cols() + col];
}

template <typename T>
T Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
    if (row < 0 || row >= rows() || col < 0 || col >= cols())
    {
        throw std::invalid_argument("Out of bounds!");
    }

    return _matrix[row * cols() + col];
}

template <typename T>
bool Matrix<T>::isSquareMatrix() const
{
    return rows() == cols();
}

template <typename T>
unsigned int Matrix<T>::rows() const
{
    return _rows;
}

template <typename T>
unsigned int Matrix<T>::cols() const
{
    return _cols;
}

template <typename T>
Matrix<T> Matrix<T>::trans() const
{
    if (! isSquareMatrix())
    {
        throw std::invalid_argument("Matrix is not square!");
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
    if (! isSquareMatrix())
    {
        throw std::invalid_argument("Matrix is not square!");
    }

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