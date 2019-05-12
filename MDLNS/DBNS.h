#pragma once
#include <tuple>
#include <cmath>
#include <map>
#include <vector>
#include <ostream>
#include <string>

#include "FiniteLengthInt.h"
#include "DBNSException.h"

template <unsigned nbits>
class DBNS
{
public:
	DBNS();
	DBNS(double base);
	DBNS(double base, int a, int b);
	DBNS(double base, FiniteLengthInt<nbits> a, FiniteLengthInt<nbits> b);
	DBNS(bool sign, double base);
	DBNS(bool sign, double base, int a, int b);
	DBNS(bool sign, double base, FiniteLengthInt<nbits> a, FiniteLengthInt<nbits> b);
	~DBNS();
	bool getSign() const;
	void setSign(bool sign);
	std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> getExponents() const;
	void setExponents(std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> exponents);
	double getBase() const;
	void setBase(double base);
	double convert();
	std::map<std::tuple<int, int>, std::tuple<int, int>> getTablePlus();
	std::map<std::tuple<int, int>, std::tuple<int, int>> getTableMinus();
	void setTables(std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus, std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus);
	DBNS<nbits> operator*(const DBNS<nbits>& other);
private:
	bool sign;
	double base;
	FiniteLengthInt<nbits> a, b;
	std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus;
	std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus;
	void setupTables();
};

template <unsigned nbits>
DBNS<nbits>::DBNS()
{
	this->sign = false;
	this->a = 0;
	this->b = 0;
	this->base = 0.0;
	this->setupTables();
}

template <unsigned nbits>
DBNS<nbits>::DBNS(double base)
{
	this->sign = false;
	this->a = 0;
	this->b = 0;
	this->base = base;
	this->setupTables();
}

template <unsigned nbits>
DBNS<nbits>::DBNS(double base, int a, int b)
{
	this->sign = false;
	this->a = FiniteLengthInt<nbits>(a);
	this->b = FiniteLengthInt<nbits>(b);
	this->base = base;
	this->setupTables();
}

template <unsigned nbits>
DBNS<nbits>::DBNS(double base, FiniteLengthInt<nbits> a, FiniteLengthInt<nbits> b)
{
	this->sign = false;
	this->a = a;
	this->b = b;
	this->base = base;
	this->setupTables();
}

template<unsigned nbits>
inline DBNS<nbits>::DBNS(bool sign, double base)
{
	this->sign = sign;
	this->a = 0;
	this->b = 0;
	this->base = base;
	this->setupTables();
}

template<unsigned nbits>
inline DBNS<nbits>::DBNS(bool sign, double base, int a, int b)
{
	this->sign = sign;
	this->a = FiniteLengthInt<nbits>(a);
	this->b = FiniteLengthInt<nbits>(b);
	this->base = base;
	this->setupTables();
}

template<unsigned nbits>
inline DBNS<nbits>::DBNS(bool sign, double base, FiniteLengthInt<nbits> a, FiniteLengthInt<nbits> b)
{
	this->sign = sign;
	this->a = a;
	this->b = b;
	this->base = base;
	this->setupTables();
}

template <unsigned nbits>
DBNS<nbits>::~DBNS()
{
}

template<unsigned nbits>
inline bool DBNS<nbits>::getSign() const
{
	return this->sign;
}

template<unsigned nbits>
inline void DBNS<nbits>::setSign(bool sign)
{
	this->sign = sign;
}

template <unsigned nbits>
std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> DBNS<nbits>::getExponents() const
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
double DBNS<nbits>::getBase() const
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

template<unsigned nbits>
inline std::map<std::tuple<int, int>, std::tuple<int, int>> DBNS<nbits>::getTablePlus()
{
	return this->tablePlus;
}

template<unsigned nbits>
inline std::map<std::tuple<int, int>, std::tuple<int, int>> DBNS<nbits>::getTableMinus()
{
	return this->tableMinus;
}

template<unsigned nbits>
inline void DBNS<nbits>::setTables(std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus, std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus)
{
	this->tablePlus = tablePlus;
	this->tableMinus = tableMinus;
}

template<unsigned nbits>
inline DBNS<nbits> DBNS<nbits>::operator*(const DBNS<nbits>& other)
{
	if (this->base != other.base) {
		throw DBNSException(this->base, other.base);
	}
	else
	{
		bool sign = (this->sign && !other.sign) || (!this->sign && other.sign);
		FiniteLengthInt<nbits> a = this->a + other.a;
		FiniteLengthInt<nbits> b = this->b + other.b;
		return DBNS<nbits>(sign, this->base, a, b);
	}
}

template <unsigned nbits>
void DBNS<nbits>::setupTables()
{
	std::map<std::pair<int, int>, double> prodMap;
	for (int x = -static_cast<int>(std::pow(2, nbits - 1)); x < static_cast<int>(std::pow(2, nbits - 1) - 1); x++) {
		for (int y = -static_cast<int>(std::pow(2, nbits - 1)); y < static_cast<int>(std::pow(2, nbits - 1) - 1); y++) {
			double prod = std::pow(2, x) * std::pow(this->base, y);
			prodMap[std::pair<int, int>(x, y)] = prod;
		}
	}

	//Searching for the most fitted correspondence
	for (auto& p : prodMap) {
		std::pair<int, int> cPhi, cPsi;
		double phi = std::abs(1.0 + p.second);
		double psi = std::abs(1.0 - p.second);
		
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
		this->tablePlus[p.first] = cPhi;
		this->tableMinus[p.first] = cPsi;
	}
}

template<unsigned nbits>
inline std::ostream& operator<<(std::ostream& os, const DBNS<nbits>& obj)
{
	std::string sign_str;
	sign_str = (obj.getSign() == true) ? "+" : "-";
	std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> exponents = obj.getExponents();
	os << sign_str << "2^(" << std::get<0>(exponents) << ")*" << obj.getBase() << "^(" << std::get<1>(exponents) << ")";
	return os;
}

void testConvert();
void testSetupTable();
void testPrintOpertor();
void testProdOperator();