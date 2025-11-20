#pragma once

#include <vector>

#include "export.hpp"

/*
 * Class Matrix
 * ------------
 * Represents a square matrix of real numbers.
 * Stores the matrix internally as a 2D vector (size n × n).
 * Provides element access via the (i, j) operator.
 * 
*/
class Matrix {
protected:
	int n;
	std::vector<std::vector<double>> data;

public:
	Matrix(int size);

	double operator()(int i, int j) const;
	double& operator()(int i, int j);
};