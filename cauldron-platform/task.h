#include "thread.h"
#pragma once

namespace cauldron::platform {
	template<class T> class task;

	// void type task - task with no result
	template<>
	class task<void> {
		template<class U> friend class task;

	public:
		task();
		virtual ~task();

		// Requests that the given thread process this task
		void post(thread::id* threadIdentifier);
		// Awaits until the task is processed
		void awaitCompletion();

		// Processes the task
		static void process(task* task);

	protected:
		virtual void procedure();

	private:
		static void postTask(task<void>& task, thread::id* threadIdentifier);

		void* _sf;
	};

	// T type task - task with result of type T
	template<class T>
	class task : private task<void> {
	public:
		using base_t = task<void>;

		template<class... ArgTs>
		task(ArgTs... args) : task<void>(), _result(args...) {}

		// Requests that the given thread process this task
		void post(thread::id* threadIdentifier) {
			postTask(*this, threadIdentifier);
		}
		
		// Awaits until the task is processed
		// Returns result of procedure
		T& awaitResult() {
			awaitCompletion();
			return _result;
		}

	protected:
		virtual void procedure(T& output) {
			/* STUB METHOD */
		};
	
	private:
		void procedure() override {
			procedure(_result);
		}
		T _result;
	};
	// void task


}