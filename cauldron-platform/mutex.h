#include "cauldron-common/macro.coreManip.h"
#pragma once
namespace cauldron::platform {
	class mutex final {
	public:
		class core_t;

		// Creates an uninitialized mutex instance
		mutex();
		// Creates an initialized mutex instance, that is optionally automatically acquired
		mutex(bool auto_acquire);
		~mutex();

		INLINE_CORE_GET(core_t, _core);
		INLINE_CORE_MOVE(mutex, core_t, _core);
		INLINE_CORE_SWAP(mutex, core_t, _core);
		
		// Returns true if mutex is initialized
		bool isInitialized() const;
		// Awaits the mutex
		bool acquire();
		// Acqires the mutex if available instantly, otherwise returns false
		bool tryAcquire();
		// Signals the mutex
		bool release();

	private:
		core_t* _core;

		mutex(const mutex&)				= delete;
		mutex& operator=(const mutex&)	= delete;
	};
}