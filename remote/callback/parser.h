#ifndef PARSER
#define PARSER

#include <string>
#include "../callback.h"

class Parser : public RemoteCallback {
private:
	std::string command;
public:
	Parser(const std::string& command);

	void Callback(
		const std::string& downloaded_data,
		SharedMemory* shared_memory
	) const;


	~Parser();
};


#endif
