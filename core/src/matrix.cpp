#include "matrix.hpp"

#include <stdexcept>

Matrix::Matrix(int size) {
	if (size < 0) {
		throw std::invalid_argument("Matrix size must not be negative!");
	}
	n = size;
	data.resize(size, std::vector<double>(size, 0.0));
}

double Matrix::operator()(int i, int j) const {
	if (i < 0 || i >= n || j < 0 || j >= n) {
		throw std::out_of_range("Matrix indices are out of range!");
	}
	return data[i][j];
}

double& Matrix::operator()(int i, int j) {
	if (i < 0 || i >= n || j < 0 || j >= n) {
		throw std::out_of_range("Matrix indices are out of range!");
	}
	return data[i][j];
}

int Matrix::size() const {
	return n;
}
