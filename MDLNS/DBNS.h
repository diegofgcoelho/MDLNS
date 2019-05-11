#pragma once
#include <tuple>
#include <cmath>
#include <map>
#include <vector>

#include "FiniteLengthInt.h"

template <unsigned nbits>
class DBNS
{
public:
	DBNS();
	DBNS(double base);
	DBNS(double base, FiniteLengthInt<nbits> a, FiniteLengthInt<nbits> b);
	~DBNS();
	std::tuple<int, int> getExponents();
	void setExponents(std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> exponents);
	double getBase();
	void setBase(double base);
	double convert();

private:
	double base;
	FiniteLengthInt<nbits> a, b;
	static std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus;
	static std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus;
	static void setupTables();
};

template <unsigned nbits>
DBNS<nbits>::DBNS()
{
	this->a = 0;
	this->b = 0;
	this->base = 0.0;
	this->setupTables();
}

template <unsigned nbits>
DBNS<nbits>::DBNS(double base)
{
	this->a = 0;
	this->b = 0;
	this->base = base;
	this->setupTables();
}

template <unsigned nbits>
DBNS<nbits>::DBNS(double base, FiniteLengthInt<nbits> a, FiniteLengthInt<nbits> b)
{
	this->a = a;
	this->b = b;
	this->base = base;
	this->setupTables();
}

template <unsigned nbits>
DBNS<nbits>::~DBNS()
{
}

template <unsigned nbits>
std::tuple<int, int> DBNS<nbits>::getExponents()
{
	return std::make_tuple(this->a, this->b);
}

template <unsigned nbits>
void DBNS<nbits>::setExponents(std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> exponents)
{
	this->a = std::get<0>(exponents);
	this->b = std::get<1>(exponents);
}

template <unsigned nbits>
double DBNS<nbits>::getBase()
{
	return this->base;
}

template <unsigned nbits>
void DBNS<nbits>::setBase(double base)
{
	this->base = base;
}

template <unsigned nbits>
double DBNS<nbits>::convert()
{
	return std::pow(2, this->a.getVal())* std::pow(this->base, this->b.getVal());
}

template <unsigned nbits>
static void DBNS<nbits>::setupTables()
{
	std::map<std::pair<int, int>, double> prodMap;
	for (int x = -std::pow(2, nbits - 1); x < std::pow(2, nbits - 1) - 1; x++) {
		for (int y = -std::pow(2, nbits - 1); y < std::pow(2, nbits - 1) - 1; y++) {
			double prod = std::pow(2, x) * std::pow(base, y);
			prodMap[std::pair<int, int>(x, y)] = prod;
		}
	}

	//Searching for the most fitted correspondence
	for (auto& p : prodMap) {
		std::pair<int, int> cPhi, cPhi;
		double phi = p.second + 1.0;
		double psi = p.second - 1.0;
		
		double bestErrPhi = 10.0;
		double bestErrPsi = 10.0;

		for (auto& q : prodMap) {
			double errPhi = std::abs(phi - q.second);
			double errPsi = std::abs(psi - q.second);
			if (errPhi < bestErrPhi) {
				cPhi = q.first;
				bestErrPhi = errPhi;
			}
			if (errPsi < bestErrPsi) {
				cPsi = q.first;
				bestErrPsi = errPsi;
			}
		}
		this->tablePlus[cPhi] = p.first;
		this->tableMinus[cPsi] = p.first;
	}
}

void testConvert();