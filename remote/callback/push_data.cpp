#include "push_data.h"

void PushCallback::Callback(
	const std::string& downloaded_data,
	SharedMemory* shared_memory
) const {
	if(shared_memory->count("push_data") == 0) {
		shared_memory->operator[]("push_data") = downloaded_data;
	} else {
		shared_memory->operator[]("push_data") += std::string(",") + downloaded_data;
	}
}
