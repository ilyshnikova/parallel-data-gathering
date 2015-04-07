#include <vector>
#include <iostream>

#include <unistd.h>
#include "operation_executer.h"

void RemoteOperationExecuter::AddOperation(
	const IP& ip,
	const Port& port,
	const RemoteCallback& remote_callback,
	SharedMemory * shared_memory

) {
	remote_operations.insert(new RemoteOperation(ip, port, remote_callback, shared_memory));
}

void RemoteOperationExecuter::ExecuteAll() {
	while (!remote_operations.empty()) {
		std::vector<RemoteOperation*> to_delete;
		for (
			std::set<RemoteOperation *>::iterator remote_operation = remote_operations.begin();
			remote_operation != remote_operations.end();
			++remote_operation
		) {
			if ((*remote_operation)->DownloadData() == 0) {
				to_delete.push_back(*remote_operation);
			}
		}
		for (size_t i = 0; i < to_delete.size(); ++i) {
			remote_operations.erase(to_delete[i]);
			delete to_delete[i];
		}
		usleep(10000);
	}
}


