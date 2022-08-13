#include "cauldron-common/macro.coreManip.h"
#pragma once
namespace cauldron::platform {
	class thread final {
	public:
		class core_t;
		class id;

		// Creates a thread object
		thread();
		// Creates a thread object and runs the procedure
		template<class arg_t>
		thread(void(*procedure)(arg_t*), arg_t* argument) : 
			_core(start((void(*)(void*))procedure, (void*)argument)) {}
		~thread();

		INLINE_CORE_GET(core_t, _core);
		INLINE_CORE_MOVE(thread, core_t, _core);
		INLINE_CORE_SWAP(thread, core_t, _core);

		// Returns true if thread is running this function is called
		bool isRunning() const;
		// Returns true if this thread is joinable
		bool isJoinable() const;
		// Returns the id of this thread
		// If this thread isnt running, then it returns nullptr
		id* getId() const;

		// Joins the thread if its joinable
		// Returns true if join is successful
		bool join();

		// Returns the id of the caller thread
		static id* getCallerId();

	private:
		core_t* _core;

		static core_t* start(void(*procedure)(void* arg), void* argument);

		thread(const thread&)				= delete;
		thread& operator=(const thread&)	= delete;
	};

}