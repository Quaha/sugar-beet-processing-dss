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

	double alpha_min;
	double alpha_max;
	double beta_1;
	double beta_2;
	bool   concentrated = false;
	bool   maturation   = false;
	bool   inorganic    = false;
	int    v = 0;
	double beta_max;

public:
	Matrix(int size);

	// Matrix(i, j) - the element in the i-th row and j-th column
	double operator()(int i, int j) const;
	double& operator()(int i, int j);

	int size() const;

	void fillMatrix(
		int    n,
		double alpha_min,
		double alpha_max,
		double beta_1,
		double beta_2,
		bool   concentrated,
		bool   maturation,
		bool   inorganic,
		int    v,
		double beta_max
	);
};