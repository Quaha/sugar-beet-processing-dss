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

	double alpha_min = 0.12;
	double alpha_max = 0.22;
	double beta_1    = 0.85;
	double beta_2    = 1.00;
	bool   concentrated = false;
	bool   maturation   = false;
	bool   inorganic    = false;
	int    v        = 0;
	double beta_max = 1.15;

public:
	Matrix(int size);

	// Matrix(i, j) - the element in the i-th row and j-th column
	double operator()(int i, int j) const;
	double& operator()(int i, int j);

	int size() const;

	void fillMatrix(
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

	double getAlphaMin()    const;
	double getAlphaMax()    const;
	double getBeta1()       const;
	double getBeta2()       const;
	bool   isConcentrated() const;
	bool   hasMaturation()  const;
	bool   isInorganic()    const;
	int    getV()           const;
	double getBetaMax()     const;
};

/*
 * Class TestableMatrix
 * ------------
 * Required for testing the Matrix class.
 * All the protected fields in it are public.
 *
*/
class TestableMatrix : public Matrix {
public:
	using Matrix::n;
	using Matrix::data;

	using Matrix::alpha_min;
	using Matrix::alpha_max;
	using Matrix::beta_1;
	using Matrix::beta_2;
	using Matrix::concentrated;
	using Matrix::maturation;
	using Matrix::inorganic;
	using Matrix::v;
	using Matrix::beta_max;
};