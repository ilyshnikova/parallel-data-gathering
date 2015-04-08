#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <unistd.h>
#include <iostream>

#include "net.h"
#include "../exception.h"
#include "operation.h"
#include "../logger.h"

RemoteOperation::RemoteOperation(
	const IP& ip,
	const Port& port,
	const RemoteCallback& remote_callback,
	SharedMemory * shared_memory
)
: port(port)
, ip(ip)
, remote_callback(remote_callback)
, shared_memory(shared_memory)
, socketfd()
, is_reading(false)
, data()
{
	int status;
	struct addrinfo host_info;

	memset(&host_info, 0, sizeof host_info);

	host_info.ai_family = AF_UNSPEC;
	host_info.ai_socktype = SOCK_STREAM;

	status = getaddrinfo(ip.c_str(), port.c_str(), &host_info, &host_info_list);
	if (status != 0) {
		throw NetworkException(std::string("getaddrinfo error") + std::string(gai_strerror(status)));
	}

	socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
	if (socketfd == -1) {
		throw NetworkException(std::string("socket error"));
	}

	status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
	if (status == -1) {
		throw NetworkException(std::string("connect error with " + ip + ":" + port));
	}


	std::string msg = "GET / HTTP/1.1\nHost:" + ip + "\nUser-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:36.0) Gecko/20100101 Firefox/36.0\n\n";

	int len = strlen(msg.c_str());
	ssize_t bytes_sent = send(socketfd, msg.c_str(), len, 0);

	logger << "Sent query to " + ip + ":" + port;
}

int RemoteOperation::DownloadData() {
	double timeout = 0;

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(socketfd, &fds);

	struct timeval tv;
	tv.tv_sec = int(timeout);
	tv.tv_usec = int((timeout - tv.tv_sec) * 1e6);

	int select_result = select(socketfd + 1, &fds, NULL, NULL, &tv);

	if (select_result < 0) {
		throw NetworkException(std::string("Err in DownloadData while selecting"));
	}

	if (select_result == 0 && is_reading) {
		logger << "Data received from " + ip + ":" + port;
		remote_callback.Callback(data, shared_memory);
		return 0;
	} else if (select_result == 1 && !is_reading) {
		is_reading = true;
	}

	if (is_reading) {
		char incoming_data_buffer[10000];
		ssize_t bytes_recieved = recv(socketfd, incoming_data_buffer, 10000, 0);

		if (bytes_recieved < 0) {
			throw NetworkException(std::string("Err in DownloadData while reading"));
		}

		data += std::string(incoming_data_buffer);

		if (bytes_recieved < 10000) {
			logger << "Data received from " + ip + ":" + port;
			remote_callback.Callback(data, shared_memory);
			return 0;
		}
	}
	return 1;
}

RemoteOperation::~RemoteOperation() {
	freeaddrinfo(host_info_list);
	close(socketfd);
}


