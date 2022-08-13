#if defined(_WIN32) || defined(_WIN64)
#include "../thread.h"
#include <Windows.h>

namespace cauldron::platform {
	struct thData {
		void(*proc)(void*);
		void* arg;
		HANDLE sem;
	};
	static unsigned long sysProc(void* arg);

	thread::thread() : _core() {}
	thread::~thread() {
		if (isJoinable())
			join();
	}
	bool thread::isRunning() const {
		return (::WaitForSingleObject(_core, 0ull) == WAIT_TIMEOUT);
	}
	bool thread::isJoinable() const {
		return isRunning() && (::GetCurrentThreadId() != ::GetThreadId(_core));
	}
	thread::id* thread::getId() const {
		return (thread::id*)GetThreadId(_core);
	}
	thread::id* thread::getCallerId() {
		return (thread::id*)GetCurrentThreadId();
	}
	bool thread::join() {
		if (!isJoinable()) return false;
		return (::WaitForSingleObject(_core, ~0ull) == WAIT_OBJECT_0);
	}
	thread::core_t* thread::start(void(*procedure)(void* arg), void* argument) {
		thData data = { procedure, argument, ::CreateSemaphoreW(nullptr, 0, 1, nullptr) };
		thread::core_t* ret = (thread::core_t*)::CreateThread(
			nullptr, 0ull,
			sysProc, &data,
			0, nullptr);
		::WaitForSingleObject(data.sem, ~0ull);
		::CloseHandle(data.sem);
		return ret;
	}

	static unsigned long sysProc(void* arg) {

		thData* data = reinterpret_cast<thData*>(arg);

		void(*proc)(void*)	= data->proc;
		void* ptr			= data->arg;
		::ReleaseSemaphore(data->sem, 1, nullptr);

		proc(ptr);

		return 0;
	}
}
#endif
