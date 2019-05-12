#include "DBNSException.h"



DBNSException::DBNSException()
{
	this->message = std::string("Incompatiable DBNS types. Unable to perform the requested operation.");
}

DBNSException::DBNSException(std::string append)
{
	this->message = message;
}

DBNSException::DBNSException(double base1, double base2)
{
	this->message = std::string("Incompatiable DBNS types. Unable to perform the requested operation.");
	this->message += std::string("Callee has base " + std::to_string(base1) + " and the called object has base " + std::to_string(base2));
}


DBNSException::~DBNSException()
{
}

void DBNSException::append(std::string str)
{
	this->message += str;
}
