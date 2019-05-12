#pragma once
#include <exception>
#include <string>

class DBNSException: public std::exception
{
public:
	DBNSException();
	DBNSException(std::string message);
	DBNSException(double base1, double base2);
	~DBNSException();
	void append(std::string str);
	virtual const char* what() const throw() {
		return this->message.c_str();
	}
private:
	std::string message;
};

