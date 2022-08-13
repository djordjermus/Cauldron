#if defined(_WIN32) || defined(_WIN64)
#include "../mutex.h"
#include <windows.h>

namespace cauldron::platform {
	mutex::mutex() :
		_core() {}
	mutex::mutex(bool auto_acquire) :
		_core((core_t*)::CreateMutexW(nullptr, auto_acquire ? TRUE : FALSE, nullptr)) {

		//if (_core == nullptr)
		//	throw;
	}
	mutex::~mutex() {
		if (_core != nullptr) {
			::CloseHandle(_core);
			_core = nullptr;
		}
	}

	bool mutex::isInitialized() const {
		return _core != nullptr;
	}
	// Awaits the semaphore
	bool mutex::acquire() {
		return (::WaitForSingleObject(_core, ~0ull) == WAIT_OBJECT_0);
	}
	// Acqires the mutex if available instantly, otherwise returns false
	bool mutex::tryAcquire() {
		return (::WaitForSingleObject(_core, 0ull) == WAIT_OBJECT_0);
	}
	// Signals the semaphore
	bool mutex::release() {
		return (::ReleaseMutex(_core) != 0);
	}
}
#endif
