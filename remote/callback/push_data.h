#ifndef PUSH_DATA
#define PUSH_DATA

#include <string>
#include "../callback.h"

class PushCallback : public RemoteCallback {
public:
	void Callback(
		const std::string& downloaded_data,
		SharedMemory* shared_memory
	) const;
};

#endif
