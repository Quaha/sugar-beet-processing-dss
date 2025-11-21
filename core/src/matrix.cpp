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

void Matrix::fillMatrix(
	double alpha_min,
	double alpha_max,
	double beta_1,
	double beta_2,
	bool   concentrated,
	bool   maturation,
	bool   inorganic,
	int    v,
	double beta_max
) {

}

double Matrix::getAlphaMin()    const { return alpha_min; }
double Matrix::getAlphaMax()    const { return alpha_max; }
double Matrix::getBeta1()       const { return beta_1; }
double Matrix::getBeta2()       const { return beta_2; }
bool   Matrix::isConcentrated() const { return concentrated; }
bool   Matrix::hasMaturation()  const { return maturation; }
bool   Matrix::isInorganic()    const { return inorganic; }
int    Matrix::getV()           const { return v; }
double Matrix::getBetaMax()     const { return beta_max; }
