#ifndef OPERATION_EXECUTER
#define OPERATION_EXECUTER

#include <set>
#include "shared_memory.h"
#include "operation.h"

class RemoteOperationExecuter{
private:
	SharedMemory shared_memory;
	std::set<RemoteOperation*> remote_operations;
public:

	void AddOperation(
		const IP& ip,
		const Port& port,
		const RemoteCallback& remote_callback,
		SharedMemory * shared_memory

	);

	void ExecuteAll();

};

#endif

