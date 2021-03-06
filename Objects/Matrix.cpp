/*Matrix class for GRLib*/
#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "matrix.h"
#include <omp.h>

// Parameter Constructor                                                                                                                                                      
template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, const T& _initial)
{
	mat.resize(_rows);
	for (unsigned i = 0; i < mat.size(); i++) {
		mat[i].resize(_cols, _initial);
	}
	rows = _rows;
	cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
{
	mat = rhs.mat;
	rows = rhs.getRows();
	cols = rhs.getCols();
}

// (Virtual) Destructor                                                                                                                                                       
template<typename T>
Matrix<T>::~Matrix() {}

// Assignment Operator                                                                                                                                                        
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if (&rhs == this)
		return *this;

	unsigned new_rows = rhs.getRows();
	unsigned new_cols = rhs.getCols();

	mat.resize(new_rows);
	for (unsigned i = 0; i < mat.size(); i++)
	{  mat[i].resize(new_cols);  }

	for (unsigned i = 0; i < new_rows; i++) 
	{
		for (unsigned j = 0; j < new_cols; j++)
		{  mat[i][j] = rhs(i, j);  }
	}
	rows = new_rows;
	cols = new_cols;

	return *this;
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) 
{
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	result(i, j) = this->mat[i][j] + rhs(i, j);	}
	}

	return result;
}

// Cumulative addition of this matrix and another                                                                                                                             
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) 
{
	unsigned rows = rhs.getRows();
	unsigned cols = rhs.getCols();

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	this->mat[i][j] += rhs(i, j);	}
	}

	return *this;
}

// Subtraction of this matrix and another                                                                                                                                     
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) 
{
	unsigned rows = rhs.getRows();
	unsigned cols = rhs.getCols();
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{  result(i, j) = this->mat[i][j] - rhs(i, j);  }
	}

	return result;
}

// Cumulative subtraction of this matrix and another                                                                                                                          
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) 
{
	unsigned rows = rhs.getRows();
	unsigned cols = rhs.getCols();

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	this->mat[i][j] -= rhs(i, j);	}
	}

	return *this;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) 
{
	unsigned rows = rhs.getRows();
	unsigned cols = rhs.getCols();
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{
			for (unsigned k = 0; k < rows; k++) 
			{
				result(i, j) += this->mat[i][k] * rhs(k, j);
			}
		}
	}

	return result;
}

// Cumulative left multiplication of this matrix and another                                                                                                                  
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) 
{
	Matrix result = (*this) * rhs;
	(*this) = result;
	return *this;
}

// Calculate a transpose of this matrix                                                                                                                                       
template<typename T>
Matrix<T> Matrix<T>::transpose() 
{
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	result(i, j) = this->mat[j][i];	}
	}

	return result;
}

// Matrix/scalar addition                                                                                                                                                     
template<typename T>
Matrix<T> Matrix<T>::operator+(const T& rhs) 
{
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	result(i, j) = this->mat[i][j] + rhs;	}
	}

	return result;
}

// Matrix/scalar subtraction                                                                                                                                                  
template<typename T>
Matrix<T> Matrix<T>::operator-(const T& rhs) 
{
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	result(i, j) = this->mat[i][j] - rhs;	}
	}

	return result;
}

// Matrix/scalar multiplication                                                                                                                                               
template<typename T>
Matrix<T> Matrix<T>::operator*(const T& rhs) 
{
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	result(i, j) = this->mat[i][j] * rhs;	}
	}

	return result;
}

// Matrix/scalar division                                                                                                                                                     
template<typename T>
Matrix<T> Matrix<T>::operator/(const T& rhs) 
{
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	result(i, j) = this->mat[i][j] / rhs;	}
	}

	return result;
}

// Multiply a matrix with a vector                                                                                                                                            
template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& rhs) 
{
	std::vector<T> result(rhs.size(), 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++) 
		{	result[i] = this->mat[i][j] * rhs[j];	}
	}

	return result;
}

// Obtain a vector of the diagonal elements                                                                                                                                   
template<typename T>
std::vector<T> Matrix<T>::diagVec() 
{
	std::vector<T> result(rows, 0.0);

	for (unsigned i = 0; i < rows; i++) 
	{	result[i] = this->mat[i][i];	}

	return result;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) 
{
	return this->mat[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const 
{
	return this->mat[row][col];
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned Matrix<T>::getRows() const 
{
	return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned Matrix<T>::getCols() const 
{
	return this->cols;
}

//Make a zero matrix
template<typedef T>
unsigned Matrix<T>::zero(unsigned _rows, unsigned _cols)
{
	Matrix<T> mat = Matrix(_rows, _cols);
	for(unsigned i=0;i<_rows;i++)
		for(unsigned j=0;j<_cols;j++)
		{	mat[i][j] = 0.0;	}

	return mat;
}

//Make a square zero matrix
template<typedef T>
unsigned Matrix<T>::zero(unsigned dimension)
{
	return zero(dimension, dimension);
}

//Make an Identity matrix
template<typedef T>
unsigned Matrix<T>::id(unsigned dimension)
{
	Matrix<T> mat = Matrix(dimension, dimension);
	for (unsigned i = 0; i < _rows; i++)
		for (unsigned j = 0; j < _cols; j++)
		{
			if(i==j)	mat[i][i] = 1.0;
			else  mat[i][j] = 0.0;
		}

	return mat;
}
//make a diag matrix
templa
<typedef T>
Matrix<T>::diag(const std::vector<T>& rhs)
{
	Matrix<T> mat = Matrix(rhs.size, rhs.size);
	for (unsigned i = 0; i < rhs.size; i++)
		for (unsigned j = 0; j < rhs.size; j++)
		{
			if (i == j)  mat[i][i] = rhs.at(i);
			else  mat[i][j] = 0.0;
		}

	return mat;
}
#endif
