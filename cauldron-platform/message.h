#include "thread.h"
#pragma once
namespace cauldron::platform {
	class message final {
	public:
		class core_t;

		// Creates an initialized instance of a message
		message();
		~message();

		INLINE_CORE_GET(core_t, _core);
		INLINE_CORE_MOVE(message, core_t, _core);
		INLINE_CORE_SWAP(message, core_t, _core);

		// Returns true if message is initialized
		bool isInitialized() const;
		// Pulls a message from the message queue, if queue is empty, it awaits for a message
		// Returns true if no errors occured
		bool awaitPull();
		// Pulls a message from the message queue, if queue is empty, it returns immediately
		// Returns true if a message was pulled from the queue
		bool immedaitePull();
		// Dispatches the contents of the message
		// A message should only ever be dispatched once
		void dispatch();

		// Generates a message queue for the calling thread
		// A thread does not by default have a message thread
		static void generateMessageQueue();
		
		// Sends a message requesting a procedure be executed on the target thread
		template<class arg_t>
		static bool post(thread::id* target, void(*procedure)(arg_t*), arg_t* argument) {
			return postLPV(
				target,
				(void(*)(void*))procedure,
				(void*)argument);
		}

	private:
		core_t* _core;

		static bool postLPV(thread::id* target, void(*procedure)(void*), void* argument);

		message(const message&)				= delete;
		message(const message&&)			= delete;
		message& operator=(const message&)	= delete;
		message& operator=(const message&&)	= delete;
	};
}