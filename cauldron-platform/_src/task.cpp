#if defined(_WIN32) || defined(_WIN64)
#include "../task.h"
#include "../message.h"
#include <windows.h>

namespace cauldron::platform {
	task<void>::task() : _sf(::CreateSemaphoreW(nullptr, 1, 1, nullptr)) {}
	task<void>::~task() {
		// Wait for task to finish, if it was sent to a thread
		::WaitForSingleObject(_sf, ~0ull);
		::CloseHandle(_sf);
	}

	void task<void>::post(thread::id* threadIdentifier) {
		postTask(*this, threadIdentifier);
	}
	void task<void>::postTask(task<void>& task, thread::id* threadIdentifier) {
		::WaitForSingleObject(task._sf, ~0ull);
		message::post(threadIdentifier, process, &task);
	}
	void task<void>::awaitCompletion() {
		::WaitForSingleObject(_sf, ~0ull);
		::ReleaseSemaphore(_sf, 1, nullptr);
	}

	void task<void>::process(task* task) {
		task->procedure();
		::ReleaseSemaphore(task->_sf, 1, nullptr);
	}
	void task<void>::procedure() {
		/* STUB METHOD*/
	}
}
#endif
