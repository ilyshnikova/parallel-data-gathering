#ifndef CALLBACK
#define CALLBACK

#include "shared_memory.h"

class RemoteCallback {
public:

	virtual void Callback(
		const std::string& downloaded_data,
		SharedMemory* shared_memory
	) const = 0;

	virtual ~RemoteCallback();
};

#endif
