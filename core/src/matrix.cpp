#include "matrix.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "utils.hpp"

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
	this->alpha_min    = alpha_min;
	this->alpha_max    = alpha_max;
	this->beta_1       = beta_1;
	this->beta_2       = beta_2;
	this->concentrated = concentrated;
	this->maturation   = maturation;
	this->inorganic    = inorganic;
	this->v            = v;
	this->beta_max     = beta_max;

	for (int i = 0; i < n; ++i) {
		data[i][0] = GetRandomDouble(alpha_min, alpha_max);
	}

	if (concentrated) {
		for (int i = 0; i < n; ++i) {
			double delta1 = GetRandomDouble(0.0, (beta_max - 1.0) / 4.0);
			double l1 = GetRandomDouble(1.0, beta_max - delta1);
			double r1 = l1 + delta1;
			for (int j = 1; j <= v; ++j) {
				double b = GetRandomDouble(l1, r1);
				data[i][j] = std::min(1.0, b * data[i][j - 1]);
			}
			double delta2 = GetRandomDouble(0.0, (beta_2 - beta_1) / 4.0);
			double l2 = GetRandomDouble(beta_1, beta_2 - delta2);
			double r2 = l2 + delta2;
			for (int j = v + 1; j < n; ++j) {
				double b = GetRandomDouble(l2, r2);
				data[i][j] = b * data[i][j - 1];
			}
		}
	} 
	else {
		for (int i = 0; i < n; ++i) {
			for (int j = 1; j <= v; ++j) {
				double b = GetRandomDouble(1.0, beta_max);
				data[i][j] = std::min(1.0, b * data[i][j - 1]);
			}
			for (int j = v + 1; j < n; ++j) {
				double b = GetRandomDouble(beta_1, beta_2);
				data[i][j] = b * data[i][j - 1];
			}
		}
	}

	if (inorganic) {
		for (int i = 0; i < n; ++i) {
			double I0 = GetRandomDouble(0.62, 0.64);
			double K = GetRandomDouble(4.8, 7.05);
			double Na = GetRandomDouble(0.21, 0.82);
			double N = GetRandomDouble(1.58, 2.8);
			for (int j = 0; j < n; ++j) {
				double I = I0 * std::pow(1.029, DAYS_PER_STAGE * j);
				double l = 1.1 + 0.1541 * (K + Na) + 0.2159 * N + 0.9989 * I + 0.1967;
				data[i][j] = data[i][j] - l / 100;
				data[i][j] = std::max(0.0, data[i][j]);
			}
		}
	}
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
