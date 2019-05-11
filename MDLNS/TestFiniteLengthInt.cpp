#include <iostream>
#include "FiniteLengthInt.h"

void testEnsureValidity() {
	const unsigned nbits = 4;
	int val = 21;
	FiniteLengthInt<nbits> fi;
	fi.setVal(val);
	int valRecovered = fi.getVal();
	std::cout << "The initial value was " << val << ". After being set to a integer with " << nbits << " bits, it became " << valRecovered << std::endl;
}

void testOperators() {
	const unsigned nbits = 4;
	int valInt = 37;
	unsigned valUnsigned = 25;
	FiniteLengthInt<nbits> finiteInt(valInt);
	FiniteLengthInt<nbits> finiteUnsigned(valUnsigned);
	FiniteLengthInt<nbits> finiteIntCopy, finiteUnsignedCopy;
	finiteIntCopy = finiteInt;
	finiteUnsignedCopy = finiteUnsigned;
	std::cout << "input int = " << valInt << " and the FiniteLength is " << finiteInt.getVal() << " and its copy is " << finiteIntCopy.getVal() << "." << std::endl;
	std::cout << "input unsigned = " << valUnsigned << " and the FiniteLength is " << finiteUnsigned.getVal() << " and its copy is " << finiteUnsignedCopy.getVal() << "." << std::endl;
	FiniteLengthInt<nbits> addResult = finiteInt + finiteUnsigned;
	std::cout << "The addition result is " << addResult.getVal() << std::endl;
	FiniteLengthInt<nbits> diffResult = finiteInt - finiteUnsigned;
	std::cout << "The difference result is " << diffResult.getVal() << std::endl;
	FiniteLengthInt<nbits> prodResult = finiteInt * finiteUnsigned;
	std::cout << "The product result is " << prodResult.getVal() << std::endl;
}