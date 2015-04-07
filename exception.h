#ifndef EXCEPTION
#define EXCEPTION

#include <exception>
#include <string>

class NetworkException : public std::exception {
private:
	std::string information;
public:
	NetworkException();
	NetworkException(const std::string& information);

	const char * what() const throw();

	~NetworkException() throw();
};

#endif
