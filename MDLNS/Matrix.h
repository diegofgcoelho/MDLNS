#pragma once
#include <algorithm>

template <class T>
class Matrix
{
public:
	//Create empty matrix
	Matrix();
	//Create matrix with dimensions (rows, cols) with all its values set to intial
	Matrix(size_t rows, size_t cols, T initial);
	//Create matrix with dimensions (rows, cols) with values as in the array initial. Initial must be rows*cols long.
	Matrix(size_t rows, size_t cols, T* initial);
	//Destroy matrix object
	~Matrix();
	//Get the element at position (row, col)
	T get(size_t row, size_t col) const;
	//Set the element at position (row, col)
	void set(size_t row, size_t col, T val);
	//Performs addition
	Matrix<T> operator+(const Matrix<T>& other) const;
	//Performs subtraction
	Matrix<T> operator-(const Matrix<T>& other) const;
	//Performs school book multiplication
	Matrix<T> operator*(const Matrix<T>& other) const;
	//Assignment operator
	Matrix<T>& operator=(const Matrix<T>& other);
	//Get rows and cols
	std::pair<size_t, size_t> getDimensions() const;
protected:
	size_t rows, cols;
	T* data;
};

template <class T>
Matrix<T>::Matrix() {
	this->rows = 0;
	this->cols = 0;
	data = nullptr;
}

template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols, T initial) {
	this->rows = rows;
	this->cols = cols;
	data = new T[this->rows*this->cols];
	//Setting all the elements
	for (size_t n = 0; n < rows; ++n)
		for (size_t k = 0; k < cols; ++k)
			data[n * cols + k] = T;
}

template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols, T* initial) {
	this->rows = rows;
	this->cols = cols;
	data = new T[this->rows * this->cols];
	//Setting all the elements
	std::copy_n(initial, this->rows * this->cols, data);	
}

template <class T>
Matrix<T>::~Matrix() {
	delete[] data;
}

template<class T>
inline T Matrix<T>::get(size_t row, size_t col) const
{
	return data[row * this->cols + col];
}

template<class T>
inline void Matrix<T>::set(size_t row, size_t col, T val)
{
	this->data[row * this->cols + col] = val;
}

template<class T>
inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
	if (this->rows != other.rows || this->cols != other.cols) {
		throw std::exception("Operation + not possible due to mismatching dimensions.");
	}
	else {
		T* result = new T[this->rows * this->cols];

		//Performing the operation
		for (size_t n = 0; n < this->rows; ++n)
			for (size_t k = 0; k < this->cols; ++k)
				result[n * this->cols + k] = this->data[n * this->cols + k] + other.data[n * this->cols + k];

		//Creating object that will be returned
		Matrix<T> mat(this->rows, this->cols, result);

		return mat;
	}
}

template<class T>
inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
	if (this->rows != other.rows || this->cols != other.cols) {
		throw std::exception("Operation - not possible due to mismatching dimensions.");
	}
	else {
		T* result = new T[this->rows * this->cols];

		//Performing the operation
		for (size_t n = 0; n < this->rows; ++n)
			for (size_t k = 0; k < this->cols; ++k)
				result[n * this->cols + k] = this->data[n * this->cols + k] - other.data[n * this->cols + k];

		//Creating object that will be returned
		Matrix<T> mat(this->rows, this->cols, result);

		return mat;
	}
}

template<class T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
	if (this->cols != other.rows) {
		throw std::exception("Operation * not possible due to mismatching dimensions.");
	}
	else {
		T* result = new T[this->rows * other.cols];

		//Performing the operation
		for (size_t n = 0; n < this->rows; ++n)
			for (size_t k = 0; k < other.cols; ++k)
			{
				result[n * other.cols + k] = this->data[n * this->cols] * other.data[k];
				for (size_t z = 1; z < this->cols; ++z)
					result[n * other.cols + k] = result[n * other.cols + k] + this->data[n * this->cols + z] * other.data[z * other.cols + k];
			}

		//Creating object that will be returned
		return Matrix<T>(this->rows, other.cols, result);
	}
}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	if (this != &other) {
		this->rows = other.rows;
		this->cols = other.cols;
		std::copy_n(other.data, this->rows * this->cols, this->data);
	}

	return *this;
}

template<class T>
inline std::pair<size_t, size_t> Matrix<T>::getDimensions() const
{
	return std::pair<size_t, size_t>(this->rows, this->cols);
}


template<class T>
inline std::ostream& operator<<(std::ostream& os, const Matrix<T>& obj)
{
	for (size_t n = 0; n < obj.getDimensions().first; ++n)
	{
		for (size_t k = 0; k < obj.getDimensions().second; ++k)
			os << obj.get(n, k) << "\t";
		os << std::endl;
	}

	return os;
}
