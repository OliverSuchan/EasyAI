#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

struct Dimension
{
    std::size_t m_rowCount;
    std::size_t m_colCount;
};

template <class T>
class Matrix
{

private:
    Dimension m_dimension;
    T** m_data;

public:
    Matrix(Dimension p_dim);
    Matrix(std::size_t p_rows, std::size_t p_cols);
    ~Matrix();
    T getVal(std::size_t p_x, std::size_t p_y);
    void setVal(T p_val, std::size_t p_x, std::size_t p_y);
    std::size_t getRowCount();
    std::size_t getColCount();

};

template <class T>
Matrix<T>::Matrix(Dimension p_dim)
{
    m_dimension = p_dim;

    m_data = new T*[m_dimension.m_rowCount];
    for(int i = 0; i < m_dimension.m_rowCount; i++)
        m_data[i] = new T[m_dimension.m_colCount];
}

template <class T>
Matrix<T>::Matrix(std::size_t p_rows, std::size_t p_cols)
    : m_dimension()
{
    m_dimension.m_rowCount = p_rows;
    m_dimension.m_colCount = p_cols;

    m_data = new T*[p_rows];
    for(int i = 0; i < p_rows; i++)
        m_data[i] = new T[p_cols];
}

template <class T>
Matrix<T>::~Matrix()
{
    for(int i = 0; i < m_dimension.m_rowCount; i++)
        delete[] m_data[i];
    delete[] m_data;
}

template <class T>
T Matrix<T>::getVal(std::size_t p_x, std::size_t p_y)
{
    return m_data[p_x][p_y];
}

template <class T>
void Matrix<T>::setVal(T p_val, std::size_t p_x, std::size_t p_y)
{
    m_data[p_x][p_y] = p_val;
}

template <class T>
std::size_t Matrix<T>::getRowCount()
{
    return m_dimension.m_rowCount;
}

template <class T>
std::size_t Matrix<T>::getColCount()
{
    return m_dimension.m_colCount;
}

#endif // MATRIX_HPP
