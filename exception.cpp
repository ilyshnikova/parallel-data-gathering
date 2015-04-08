#include "exception.h"

NetworkException::NetworkException()
: std::exception()
, information()
{}

NetworkException::NetworkException(const std::string& information)
: std::exception()
, information (information)
{}

const char * NetworkException::what() const throw() {
	return information.c_str();
}

NetworkException::~NetworkException() throw() {}
