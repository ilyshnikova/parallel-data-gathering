#include <iostream>

#include "remote/callback/parser.h"
#include "remote/callback/push_data.h"
#include "remote/operation_executer.h"
#include "remote/operation.h"
#include "logger.h"


#include "execute.h"

int main() {
	PushCallback push_callback;
	SharedMemory shared_memory;
	RemoteOperationExecuter remote_operation_executer;

	Parser banki_parser = Parser(
		"awk 1 ORS=' ' | LANG=C sed 's/.*currency-informer__yesterday-column\">//g' | LANG=C sed 's/<.*//g' | sed 's/,/./g'"
	);
	Parser local_parser = Parser("awk 1 ORS=' ' | LANG=C sed 's/.*Currency is now//g'");

	logger << "Started";

	remote_operation_executer.AddOperation(std::string("www.banki.ru"), std::string("80"), banki_parser, &shared_memory);
	remote_operation_executer.AddOperation(std::string("127.0.0.1"), std::string("8000"), local_parser, &shared_memory);
	remote_operation_executer.ExecuteAll();

	logger << "Result = " + shared_memory["push_data"];
	logger << "Done";

	return 0;
}
