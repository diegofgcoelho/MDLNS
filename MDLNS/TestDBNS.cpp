#include <iostream>
#include "DBNS.h"

void testConvert() {
	const unsigned nbits = 5;
	FiniteLengthInt<nbits> a(25);
	FiniteLengthInt<nbits> b(-37);
	double base = 3.0;
	DBNS<nbits> x(base, a, b);
	std::cout << "DBNS with " << nbits << " bits and base " << base << " with exponents (" << a.getVal() << ", " << b.getVal() << ") = " << x.convert() << std::endl;
}

void testSetupTable() {
	const unsigned nbits = 3;
	FiniteLengthInt<nbits> a(25);
	FiniteLengthInt<nbits> b(-37);
	double base = 3.0;
	DBNS<nbits> x(base, a, b);
	std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus = x.getTableMinus();
	std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus = x.getTablePlus();
	std::cout << "Minus table:" << std::endl;
	for (auto& v : tableMinus) {
		double prod = std::pow(2, std::get<0>(v.second)) * std::pow(base, std::get<1>(v.second));
		double psi = std::abs(1.0 - std::pow(2, std::get<0>(v.first)) * std::pow(base, std::get<1>(v.first)));
		double dist = std::abs(psi - prod);
		std::cout << "(" << std::get<0>(v.first) << ", " << std::get<1>(v.first) << ") -> (" << std::get<0>(v.second) << ", " << std::get<1>(v.second) << ")"  << " distance = " << dist << std::endl;
	}
	std::cout << "Plus table:" << std::endl;
	for (auto& v : tablePlus) {
		double prod = std::pow(2, std::get<0>(v.second)) * std::pow(base, std::get<1>(v.second));
		double psi = std::abs(1.0 + std::pow(2, std::get<0>(v.first)) * std::pow(base, std::get<1>(v.first)));
		double dist = std::abs(psi - prod);
		std::cout << "(" << std::get<0>(v.first) << ", " << std::get<1>(v.first) << ") -> (" << std::get<0>(v.second) << ", " << std::get<1>(v.second) << ")" << " distance = " << dist << std::endl;
	}
}

void testPrintOpertor() {
	const unsigned nbits = 5;
	FiniteLengthInt<nbits> a(25);
	FiniteLengthInt<nbits> b(-37);
	double base = 3.0;
	DBNS<nbits> x(base, a, b);
	DBNS<nbits> y(base, 1, 4);
	std::cout << x << std::endl;
	std::cout << y << std::endl;
}


void testProdOperator() {
	const unsigned nbits = 5;
	FiniteLengthInt<nbits> a(25);
	FiniteLengthInt<nbits> b(-37);
	double base = 3.0;
	DBNS<nbits> x(base, a, b);
	DBNS<nbits> y(base, 1, 4);
	DBNS<nbits> z(base, a, b);
	z = x * y;
	std::cout << " x = " << x << " , y =  " << y << " -> z = " << z << " - > diff = " << std::abs(z.convert()-x.convert()*y.convert()) << std::endl;
}

void testDivOperator() {
	const unsigned nbits = 5;
	FiniteLengthInt<nbits> a(25);
	FiniteLengthInt<nbits> b(-37);
	double base = 3.0;
	DBNS<nbits> x(base, a, b);
	DBNS<nbits> y(base, 1, 4);
	DBNS<nbits> z(base, a, b);
	z = x / y;
	std::cout << " x = " << x << " , y =  " << y << " -> z = " << z << " - > diff = " << std::abs(z.convert() - x.convert() / y.convert()) << std::endl;
}

void testAddOperator() {
	const unsigned nbits = 5;
	FiniteLengthInt<nbits> a(25);
	FiniteLengthInt<nbits> b(-37);
	double base = 3.0;
	DBNS<nbits> x(base, a, b);
	DBNS<nbits> y(base, 1, 4);
	DBNS<nbits> z(base, a, b);
	z = x + y;
	std::cout << " x = " << x << " , y =  " << y << " -> z = " << z << " - > add = " << std::abs(z.convert() - (x.convert() + y.convert())) << std::endl;
	std::cout << "x.convert = " << x.convert() << std::endl;
	std::cout << "y.convert = " << y.convert() << std::endl;
	std::cout << "z.convert = " << z.convert() << std::endl;
}

void testSubOperator() {
	const unsigned nbits = 5;
	FiniteLengthInt<nbits> a(25);
	FiniteLengthInt<nbits> b(-37);
	double base = 3.0;
	DBNS<nbits> x(base, a, b);
	DBNS<nbits> y(base, 1, 4);
	DBNS<nbits> z(base, a, b);
	z = x - y;
	std::cout << " x = " << x << " , y =  " << y << " -> z = " << z << " - > diff = " << std::abs(z.convert() - (x.convert() - y.convert())) << std::endl;
}
