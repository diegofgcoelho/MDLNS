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

void testSetuTable() {
	const unsigned nbits = 5;
	FiniteLengthInt<nbits> a(25);
	FiniteLengthInt<nbits> b(-37);
	double base = 3.0;
	DBNS<nbits> x(base, a, b);
	

}