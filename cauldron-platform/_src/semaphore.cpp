#if defined(_WIN32) || defined(_WIN64)
#include "../semaphore.h"
#include <Windows.h>

namespace cauldron::platform {

	semaphore::semaphore() :
		_core() {}
	semaphore::semaphore(u32 count, u32 maximum) :
		_core((core_t*)::CreateSemaphoreW(nullptr, count, maximum, nullptr)) {
	}
	semaphore::~semaphore() {
		if (_core != nullptr) {
			::CloseHandle(_core);
			_core = nullptr;
		}
	}
	bool semaphore::isInitialized() const {
		return _core != nullptr;
	}
	bool semaphore::acquire() {
		return (::WaitForSingleObject(_core, ~0ull) == WAIT_OBJECT_0);
	}
	bool semaphore::tryAcquire() {
		return (::WaitForSingleObject(_core, 0ull) == WAIT_OBJECT_0);
	}
	bool semaphore::release() {
		return (::ReleaseSemaphore(_core, 1, nullptr) != 0);
	}
}
#endif
