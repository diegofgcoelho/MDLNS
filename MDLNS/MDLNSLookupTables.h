#pragma once
#include <tuple>
#include <cmath>
#include <map>

//This class holds all the lookup tables required for MDLNS 
//functioning and allow it to be instantiated only once (Singleton)

template <unsigned nbits>
class MDLNSLookupTables
{
private:
	static MDLNSLookupTables<nbits> obj;
	MDLNSLookupTables();

	std::map<std::tuple<int, int>, std::tuple<int, int>> tablePlus;
	std::map<std::tuple<int, int>, std::tuple<int, int>> tableMinus;
	std::map<std::tuple<int, int>, int> tableSBD;
	void setupTablesPlusAndMinus();
	void setupTableSBD();

public:
	static MDLNSLookupTables<nbits> getInstance() {
		if (obj == nullptr)
			obj = new MDLNSLookupTables < nbits >();
		return obj;
	}

	std::tuple<int, int> consultPlusTable(std::tuple<int, int>& key) const;
	std::tuple<int, int> consultMinusTable(std::tuple<int, int>& key) const;
	int consultSBD(std::tuple<int, int>& key) const;
};

template<unsigned nbits>
inline void MDLNSLookupTables<nbits>::setupTablesPlusAndMinus()
{
	std::map<std::pair<int, int>, double> prodMap;
	for (int x = -static_cast<int>(std::pow(2, nbits - 1)); x < static_cast<int>(std::pow(2, nbits - 1)); x++) {
		for (int y = -static_cast<int>(std::pow(2, nbits - 1)); y < static_cast<int>(std::pow(2, nbits - 1)); y++) {
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
inline void MDLNSLookupTables<nbits>::setupTableSBD()
{
	std::map<std::tuple<int, int>, int> SBDMap;
	for (int x = -static_cast<int>(std::pow(2, nbits - 1)); x < static_cast<int>(std::pow(2, nbits - 1)); x++) {
		for (int y = -static_cast<int>(std::pow(2, nbits - 1)); y < static_cast<int>(std::pow(2, nbits - 1)); y++) {
			double v = x + y * std::log2(this->base);
			//v = std::round(v * std::pow(2.0, nbits-1));
			v = std::round(v);
			SBDMap[std::tuple<int, int>(x, y)] = FiniteLengthInt<2 * nbits>(static_cast<int>(v)).getVal();
		}
	}
	this->tableSBD = SBDMap;
}

template<unsigned nbits>
inline std::tuple<int, int> MDLNSLookupTables<nbits>::consultPlusTable(std::tuple<int, int>& key) const
{
	return this->tablePlus[key];
}

template<unsigned nbits>
inline std::tuple<int, int> MDLNSLookupTables<nbits>::consultMinusTable(std::tuple<int, int>& key) const
{
	return this->tableMinus[key];
}

template<unsigned nbits>
inline int MDLNSLookupTables<nbits>::consultSBD(std::tuple<int, int>& key) const
{
	return this->tableSBD[key];
}
