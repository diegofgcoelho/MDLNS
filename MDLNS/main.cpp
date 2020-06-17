// MDLNS0.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>

#include "FiniteLengthInt.h"
#include "DBNS.h"
#include "Matrix.h"

//#define LNS
#define MDLNS
//#define BINARY

//Study of the numerical error due to conversion/representation in MDLNS
void experiment_conversion_numerical_precision() {

	const size_t NSAMPLES = 1000;
	std::mt19937 generator;
	std::normal_distribution<double> normal(0.0, 1.0);

#ifdef LNS
	const unsigned nbits = 8;
	const double e = 1.0;
	const double scale = 1.0;
#endif // LNS

#ifdef MDLNS
	const unsigned nbits = 4;
	//const double e = std::exp(1);
	const double e = std::sqrt(std::sqrt(std::sqrt(std::sqrt(std::exp(1)))));
	//const double e = std::pow(2, (1 + std::sqrt(5)) / 2);
	const double scale = 1.0;
#endif // MDLNS

#ifdef BINARY
	const unsigned nbits = 8;
	const double scale = std::pow(2, 5);
#endif // BINARY


#ifndef BINARY
	FiniteLengthInt<nbits> a(0), b(0);
	DBNS<nbits> x(e, a, b);

	std::vector<double> errs(NSAMPLES, 0.0);
	std::vector<double> ds(NSAMPLES, 0.0);

	std::ofstream file("mdlns_errors.txt");
	for (size_t t = 0; t < NSAMPLES; ++t) {
		//Generating number to convert
		double d = normal(generator);
		x.convert(d * scale);
		//Calculating the error due to the MDLNS representation
		errs[t] = d - x.convert() / scale;
		ds[t] = d;
	}

	for (size_t t = 0; t < NSAMPLES; ++t) {
		file << ds[t] << "\t" << errs[t] << std::endl;
	}

	file.close();
#else
	FiniteLengthInt<nbits> a(0);

	std::vector<double> errs(NSAMPLES, 0.0);
	std::vector<double> ds(NSAMPLES, 0.0);

	std::ofstream file("mdlns_errors.txt");
	for (size_t t = 0; t < NSAMPLES; ++t) {
		//Generating number to convert
		double d = normal(generator);
		a.setVal(static_cast<int>(std::round(d * scale)));
		//Calculating the error due to the MDLNS representation
		errs[t] = d - a.getVal() / scale;
		ds[t] = d;
	}

	for (size_t t = 0; t < NSAMPLES; ++t) {
		file << ds[t] << "\t" << errs[t] << std::endl;
	}

	file.close();
#endif // BINARY
}

//Study of the numerical error due to conversion/representation in matrix multiplication using MDLNS
void experiment_matrix_matrix_multiplication_numerical_precision(size_t nsamples = 10, size_t nrows1 = 3, size_t ncols1 = 7, size_t nrows2 = 7, size_t ncols2 = 10) {

	std::ofstream file("mdlns_mm_errors.txt");

	std::mt19937 generator;
	std::normal_distribution<double> normal(0.0, 1.0);

	const unsigned nbits = 5;
	const double e = std::exp(1);
	const double scale = 1.0;

	//Data in double format
	double* x = new double[nrows1 * ncols1];
	double* y = new double[nrows2 * ncols2];

	//Data in DBNS format
	DBNS<nbits>* x_dbns = new DBNS<nbits>[nrows1 * ncols1];
	DBNS<nbits>* y_dbns = new DBNS<nbits>[nrows2 * ncols2];
	
	for (size_t sample = 0; sample < nsamples; ++sample) {
		std::cout << "Starting sample " << sample << "/" << nsamples << std::endl;
		//Errors before and after the matrix product
		double input_errs_A = 0.0;
		double input_errs_B = 0.0;
		double output_errs = 0.0;
		
		//Generating data to be converted to DBNS matrix A
		for (size_t n = 0; n < nrows1 * ncols1; ++n) {
			double d = normal(generator);
			x[n] = d;
			x_dbns[n].setSign(true);
			x_dbns[n].setBase(e);
			x_dbns[n].convert(d * scale);

			input_errs_A += std::abs(d - x_dbns[n].convert() / scale);
		}
		input_errs_A /= (nrows1 * ncols1);

		Matrix<double> A(nrows1, ncols1, x);
		Matrix<DBNS<nbits>> A_DBNS(nrows1, ncols1, x_dbns);

		//Generating data to be converted to DBNS matrix B
		for (size_t n = 0; n < nrows2 * ncols2; ++n) {
			double d = normal(generator);
			y[n] = d;
			y_dbns[n].setSign(true);
			y_dbns[n].setBase(e);
			y_dbns[n].convert(d * scale);

			input_errs_B += std::abs(d - y_dbns[n].convert() / scale);
		}
		input_errs_B /= (nrows2 * ncols2);

		Matrix<double> B(nrows2, ncols2, y);
		Matrix<DBNS<nbits>> B_DBNS(nrows2, ncols2, y_dbns);

		std::cout << "Generated matrices A and B." << std::endl;

		Matrix<double> C = A * B;
		std::cout << "A * B in double format done" << std::endl;
		Matrix<DBNS<nbits>> C_DBNS = A_DBNS * B_DBNS;
		std::cout << "A * B in DBNS format done" << std::endl;

		//Computing the error resulting from the matrix product in DBNS format
		for (size_t n = 0; n < nrows1; ++n)
			for (size_t k = 0; k < ncols2; ++k)
				output_errs += std::abs(C.get(n, k) - C_DBNS.get(n, k).convert() / (scale * scale));
		output_errs /= (nrows1 * ncols2);

		std::cout.precision(5);
		std::cout << "A = " << std::endl; std::cout << A;
		std::cout << "Adb = " << std::endl; std::cout << A_DBNS;
		std::cout << "B = " << std::endl; std::cout << B;
		std::cout << "Bdb = " << std::endl; std::cout << B_DBNS;
		std::cout << "C = " << std::endl; std::cout << C;
		std::cout << "Cdb = " << std::endl; std::cout << C_DBNS;
		std::cout.precision();

		file << input_errs_A << "\t" << input_errs_B << "\t" << output_errs << std::endl;
		std::cout << input_errs_A << "\t" << input_errs_B << "\t" << output_errs << std::endl;
		std::cout << "Finished sample " << sample << "/" << nsamples << std::endl;
	}


	delete[] x;
	delete[] y;
	delete[] x_dbns;
	delete[] y_dbns;
	file.close();

}

int main()
{
	//testEnsureValidity();
	//testOperators();
	//testConvert();
	//testSetupTable();
	//testPrintOpertor();
	//testProdOperator();
	//testDivOperator();
	//testAddOperator();
	//testSubOperator();
	//testUnarySubOperator();
	//testConvertFromNumber();
	//testAddSBD();

	//experiment_conversion_numerical_precision();
	experiment_matrix_matrix_multiplication_numerical_precision();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
