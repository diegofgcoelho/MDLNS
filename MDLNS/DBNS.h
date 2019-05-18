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
	DBNS(const DBNS<nbits>& other);
	~DBNS();
	bool getSign() const;
	void setSign(bool sign);
	std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> getExponents() const;
	void setExponents(std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> exponents);
	double getBase() const;
	void setBase(double base);
	double convert();
	std::map<std::tuple<int, int>, std::tuple<int, int>> getTablePlus() const;
	std::map<std::tuple<int, int>, std::tuple<int, int>> getTableMinus() const;
	void setTables(const std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus, const std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus);
	bool operator<(const DBNS<nbits>& other) const;
	bool operator>(const DBNS<nbits>& other) const;
	bool operator==(const DBNS<nbits>& other) const;
	DBNS<nbits> operator*(const DBNS<nbits>& other) const;
	DBNS<nbits> operator/(const DBNS<nbits>& other) const;
	DBNS<nbits> operator+(const DBNS<nbits>& other) const;
	DBNS<nbits> operator-(const DBNS<nbits>& other) const;
private:
	bool sign;
	double base;
	FiniteLengthInt<nbits> a, b;
	std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus;
	std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus;
	std::map<std::tuple<int, int>, int> tableSBD;
	void setupTablesPlusAndMinus();
	void setupTableSBD();
};

template <unsigned nbits>
DBNS<nbits>::DBNS()
{
	this->sign = false;
	this->a = 0;
	this->b = 0;
	this->base = 0.0;
	this->setupTablesPlusAndMinus();
	this->setupTableSBD();
}

template <unsigned nbits>
DBNS<nbits>::DBNS(double base)
{
	this->sign = false;
	this->a = 0;
	this->b = 0;
	this->base = base;
	this->setupTablesPlusAndMinus();
	this->setupTableSBD();
}

template <unsigned nbits>
DBNS<nbits>::DBNS(double base, int a, int b)
{
	this->sign = false;
	this->a = FiniteLengthInt<nbits>(a);
	this->b = FiniteLengthInt<nbits>(b);
	this->base = base;
	this->setupTablesPlusAndMinus();
	this->setupTableSBD();
}

template <unsigned nbits>
DBNS<nbits>::DBNS(double base, FiniteLengthInt<nbits> a, FiniteLengthInt<nbits> b)
{
	this->sign = false;
	this->a = a;
	this->b = b;
	this->base = base;
	this->setupTablesPlusAndMinus();
	this->setupTableSBD();
}

template<unsigned nbits>
inline DBNS<nbits>::DBNS(bool sign, double base)
{
	this->sign = sign;
	this->a = 0;
	this->b = 0;
	this->base = base;
	this->setupTablesPlusAndMinus();
	this->setupTableSBD();
}

template<unsigned nbits>
inline DBNS<nbits>::DBNS(bool sign, double base, int a, int b)
{
	this->sign = sign;
	this->a = FiniteLengthInt<nbits>(a);
	this->b = FiniteLengthInt<nbits>(b);
	this->base = base;
	this->setupTablesPlusAndMinus();
	this->setupTableSBD();
}

template<unsigned nbits>
inline DBNS<nbits>::DBNS(bool sign, double base, FiniteLengthInt<nbits> a, FiniteLengthInt<nbits> b)
{
	this->sign = sign;
	this->a = a;
	this->b = b;
	this->base = base;
	this->setupTablesPlusAndMinus();
	this->setupTableSBD();
}

template<unsigned nbits>
inline DBNS<nbits>::DBNS(const DBNS<nbits>& other)
{
	this->sign = other.sign;
	this->a = other.a;
	this->b = other.b;
	this->base = other.base;
	this->tablePlus = other.getTablePlus();
	this->tableMinus = other.getTableMinus();
	this->tableSBD = other.tableSBD;
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
inline std::map<std::tuple<int, int>, std::tuple<int, int>> DBNS<nbits>::getTablePlus() const
{
	return this->tablePlus;
}

template<unsigned nbits>
inline std::map<std::tuple<int, int>, std::tuple<int, int>> DBNS<nbits>::getTableMinus() const
{
	return this->tableMinus;
}

template<unsigned nbits>
inline void DBNS<nbits>::setTables(const std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus, const std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus)
{
	this->tablePlus = tablePlus;
	this->tableMinus = tableMinus;
}

template<unsigned nbits>
inline bool DBNS<nbits>::operator<(const DBNS<nbits>& other) const
{
	int thisv = this->tableSBD.at(std::pair<int, int>(this->a.getVal(), this->b.getVal()));
	int otherv = this->tableSBD.at(std::pair<int, int>(other.a.getVal(), other.b.getVal()));
	return (thisv < otherv);
}

template<unsigned nbits>
inline bool DBNS<nbits>::operator>(const DBNS<nbits>& other) const
{
	int thisv = this->tableSBD.at(std::pair<int, int>(this->a.getVal(), this->b.getVal()));
	int otherv = this->tableSBD.at(std::pair<int, int>(other.a.getVal(), other.b.getVal()));
	return (thisv > otherv);
}

template<unsigned nbits>
inline bool DBNS<nbits>::operator==(const DBNS<nbits>& other) const
{
	int thisv = this->tableSBD.at(std::pair<int, int>(this->a.getVal(), this->b.getVal()));
	int otherv = this->tableSBD.at(std::pair<int, int>(other.a.getVal(), other.b.getVal()));
	return (thisv == otherv);
}

template<unsigned nbits>
inline DBNS<nbits> DBNS<nbits>::operator*(const DBNS<nbits>& other) const
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

template<unsigned nbits>
inline DBNS<nbits> DBNS<nbits>::operator/(const DBNS<nbits>& other) const
{
	if (this->base != other.base) {
		throw DBNSException(this->base, other.base);
	}
	else
	{
		bool sign = (this->sign && !other.sign) || (!this->sign && other.sign);
		FiniteLengthInt<nbits> a = this->a - other.a;
		FiniteLengthInt<nbits> b = this->b - other.b;
		return DBNS<nbits>(sign, this->base, a, b);
	}
}

template<unsigned nbits>
inline DBNS<nbits> DBNS<nbits>::operator+(const DBNS<nbits>& other) const
{

	if (this->base != other.base) {
		throw DBNSException(this->base, other.base);
	}
	else
	{
		if (this->sign == other.sign) {
			const DBNS<nbits>* left = (*this > other) ? this : &other;
			const DBNS<nbits>* right = (*this > other) ? &other : this;

			std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> leftExp = left->getExponents();
			std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> rightExp = right->getExponents();
			std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> addExp = std::make_tuple(std::get<0>(rightExp) + std::get<0>(leftExp), std::get<1>(rightExp) + std::get<1>(leftExp));

			std::tuple<int, int> prod;
			int first = std::get<0>(addExp).getVal();
			int second = std::get<1>(addExp).getVal();
			prod = this->tablePlus.at(std::make_tuple(first, second));

			leftExp = std::make_tuple(std::get<0>(leftExp) + FiniteLengthInt<nbits>(std::get<0>(prod)), std::get<1>(leftExp) + FiniteLengthInt<nbits>(std::get<1>(prod)));
			DBNS<nbits> result(this->sign, this->base, std::get<0>(leftExp), std::get<1>(leftExp));
			return result;
		}
		else if (this->sign == true && other.sign == false) {
			DBNS<nbits> subtractor(*this);
			subtractor.setSign(false);
			return other - subtractor;
		}
		//else if (this->sign == false && other.sign == true) {
		else {
			DBNS<nbits> subtractor(other);
			subtractor.setSign(false);
			return (*this) - subtractor;
		}
	}
}

template<unsigned nbits>
inline DBNS<nbits> DBNS<nbits>::operator-(const DBNS<nbits>& other) const
{

	if (this->base != other.base) {
		throw DBNSException(this->base, other.base);
	}
	else
	{
		if (this->sign == other.sign) {
			const DBNS<nbits>* left = this;
			const DBNS<nbits>* right = &other;

			std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> leftExp = left->getExponents();
			std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> rightExp = right->getExponents();
			std::tuple<FiniteLengthInt<nbits>, FiniteLengthInt<nbits>> addExp = std::make_tuple(std::get<0>(rightExp) - std::get<0>(leftExp), std::get<1>(rightExp) - std::get<1>(leftExp));

			std::tuple<int, int> prod;
			prod = this->tableMinus.at(std::tuple<int, int>(std::get<0>(addExp).getVal(), std::get<1>(addExp).getVal()));

			leftExp = std::make_tuple(std::get<0>(leftExp) + FiniteLengthInt<nbits>(std::get<0>(prod)), std::get<1>(leftExp) + FiniteLengthInt<nbits>(std::get<1>(prod)));
			DBNS<nbits> result(this->sign, this->base, std::get<0>(leftExp), std::get<1>(leftExp));
			return result;
		}
		//else if (this->sign != other.sign) {
		else {
			DBNS<nbits> adder(*this);
			adder.setSign(!this->sign);
			return other + adder;
		}
	}
}

template <unsigned nbits>
void DBNS<nbits>::setupTablesPlusAndMinus()
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
		double phi = (1.0 + p.second);
		double psi = (1.0 - p.second);
		
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
inline void DBNS<nbits>::setupTableSBD()
{
	std::map<std::tuple<int, int>, int> SBDMap;
	for (int x = -static_cast<int>(std::pow(2, nbits - 1)); x < static_cast<int>(std::pow(2, nbits - 1) - 1); x++) {
		for (int y = -static_cast<int>(std::pow(2, nbits - 1)); y < static_cast<int>(std::pow(2, nbits - 1) - 1); y++) {
			double v = x + y * std::log2(this->base);
			v = std::round(v * std::pow(2.0, nbits-1));
			SBDMap[std::tuple<int, int>(x, y)] = FiniteLengthInt<2*nbits>(static_cast<int>(v)).getVal();
		}
	}
	this->tableSBD = SBDMap;
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
void testDivOperator();
void testAddOperator();
void testSubOperator();