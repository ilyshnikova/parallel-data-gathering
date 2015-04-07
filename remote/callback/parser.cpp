#include <iostream>
#include <fstream>


#include "parser.h"
#include "../../execute.h"

Parser::Parser(const std::string& command)
: command(std::string(command))
{}

void Parser::Callback(
	const std::string& downloaded_data,
	SharedMemory* shared_memory
) const {

	std::ofstream out("tmp.txt");
	out << downloaded_data;
	out.close();

	std::string external_command = std::string("cat tmp.txt | \0") + command + std::string(" && rm tmp.txt\0");
	ExecuteHandler eh(external_command);

	std::string string;
	while (eh >> string) {
		if(shared_memory->count("push_data") == 0) {
			shared_memory->operator[]("push_data") = string;
		} else {
			shared_memory->operator[]("push_data") += std::string(",") + string;
		}
	}

}

Parser::~Parser() {}
