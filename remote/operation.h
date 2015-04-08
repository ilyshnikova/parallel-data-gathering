#ifndef OPERATION
#define OPERATION

#include "net.h"
#include "shared_memory.h"
#include "callback.h"

class RemoteOperation{
private:
	Port port;
	IP ip;
	const RemoteCallback& remote_callback;
	SharedMemory* shared_memory;
	int socketfd;
	bool is_reading;
	std::string data;
	struct addrinfo * host_info_list;

public:

	RemoteOperation(
		const IP& ip,
		const Port& port,
		const RemoteCallback& remote_callback,
		SharedMemory * shared_memory
	);

	RemoteCallback * clone();

	int DownloadData();

	~RemoteOperation();
};

#endif
