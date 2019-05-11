#pragma once
template <unsigned nbits> class FiniteLengthInt
{
public:
	FiniteLengthInt();
	FiniteLengthInt(int val);
	FiniteLengthInt(unsigned val);
	~FiniteLengthInt();
	int getVal() const;
	void setVal(int val);
	void setVal(unsigned val);
	FiniteLengthInt<nbits>& operator=(const FiniteLengthInt<nbits>& other);
	FiniteLengthInt<nbits>& operator=(const int& other);
	FiniteLengthInt<nbits>& operator=(const unsigned& other);
	FiniteLengthInt<nbits> operator+(const FiniteLengthInt<nbits>& other);
	FiniteLengthInt<nbits> operator-(const FiniteLengthInt<nbits>& other);
	FiniteLengthInt<nbits> operator*(const FiniteLengthInt<nbits>& other);
	FiniteLengthInt<nbits> operator<<(const unsigned& n);
	FiniteLengthInt<nbits> operator>>(const unsigned& n);
private:
	const unsigned bits = nbits;
	int val;
	//Ensure the validity of the current value in val
	void ensureValidity();
};

template<unsigned nbits>
FiniteLengthInt<nbits>::FiniteLengthInt()
{
	this->val = 0;
}

template<unsigned nbits>
FiniteLengthInt<nbits>::FiniteLengthInt(int val)
{
	this->setVal(val);
}

template<unsigned nbits>
FiniteLengthInt<nbits>::FiniteLengthInt(unsigned val)
{
	this->setVal(static_cast<int>(val));
}

template<unsigned nbits>
FiniteLengthInt<nbits>::~FiniteLengthInt()
{
}

template<unsigned nbits>
int FiniteLengthInt<nbits>::getVal() const
{
	return this->val;
}

template<unsigned nbits>
void FiniteLengthInt<nbits>::setVal(int val)
{
	this->val = val;
	this->ensureValidity();
}

template<unsigned nbits>
void FiniteLengthInt<nbits>::setVal(unsigned val)
{
	this->val = static_cast<int>(val);
	this->ensureValidity();
}


template<unsigned nbits>
void FiniteLengthInt<nbits>::ensureValidity()
{
	//Checking the sign of the finite lenght int
	bool sign = (this->val >> (nbits - 1)) & 1;
	//If sign = 0, finalVal starts with 0, otherwise -1 (set all the bits to 1)

	int finalVal = 0;
	if (sign == false) {
		//Setting the bits values other than the sign
		for (unsigned int v = 0; v < nbits - 1; v++) {
			bool d = (this->val >> v) & 1;
			finalVal |= d << v;
		}
	}
	else {
		finalVal = -1;
		//Setting the bits values other than the sign
		for (unsigned int v = 0; v < nbits - 1; v++) {
			bool d = (this->val >> v) & 1;
			unsigned mask = (d == true) ? -1 : ~(1 << v);
			finalVal &= mask;
			//finalVal &= ~(d << v);
		}
	}
	this->val = finalVal;
}

template<unsigned nbits>
FiniteLengthInt<nbits> & FiniteLengthInt<nbits>::operator=(const FiniteLengthInt<nbits> & other) {
	if (this != &other) {
		this->val = other.val;
	}
	return *this;
}

template<unsigned nbits>
FiniteLengthInt<nbits>& FiniteLengthInt<nbits>::operator=(const int& other) {
	if (this != &other) {
		this->setVal(other);
	}
	return *this;
}

template<unsigned nbits>
FiniteLengthInt<nbits>& FiniteLengthInt<nbits>::operator=(const unsigned& other) {
	if (this != &other) {
		this->setVal(other);
	}
	return *this;
}

template<unsigned nbits>
FiniteLengthInt<nbits> FiniteLengthInt<nbits>::operator+(const FiniteLengthInt<nbits> & other) {
	FiniteLengthInt<nbits> output;
	output.setVal(this->val + other.getVal());
	return output;
}

template<unsigned nbits>
FiniteLengthInt<nbits> FiniteLengthInt<nbits>::operator-(const FiniteLengthInt<nbits> & other) {
	FiniteLengthInt<nbits> output;
	output.setVal(this->val - other.getVal());
	return output;
}

template<unsigned nbits>
FiniteLengthInt<nbits> FiniteLengthInt<nbits>::operator*(const FiniteLengthInt<nbits>& other) {
	FiniteLengthInt<nbits> output;
	output.setVal(this->val * other.getVal());
	return output;
}

template<unsigned nbits>
FiniteLengthInt<nbits> FiniteLengthInt<nbits>::operator<<(const unsigned& n) {
	FiniteLengthInt<nbits> output;
	output.setVal(this->val << n);
	return output;
}

template<unsigned nbits>
FiniteLengthInt<nbits> FiniteLengthInt<nbits>::operator>>(const unsigned& n) {
	FiniteLengthInt<nbits> output;
	output.setVal(this->val >> n);
	return output;
}


void testEnsureValidity();
void testOperators();

