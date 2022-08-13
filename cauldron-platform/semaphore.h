#include "cauldron-common/primitives.h"
#include "cauldron-common/macro.coreManip.h"
#pragma once
namespace cauldron::platform {

	class semaphore final {
	public:
		class core_t;


		// Creates an uninitialized semaphore instance
		semaphore();
		// Creates an initialized semaphore instance with given parameters
		semaphore(u32 count, u32 maximum);
		~semaphore();

		INLINE_CORE_GET(core_t, _core);
		INLINE_CORE_MOVE(semaphore, core_t, _core);
		INLINE_CORE_SWAP(semaphore, core_t, _core);

		// Returns true if semaphore is initialized
		bool isInitialized() const;
		// Awaits the semaphore
		bool acquire();
		// Acqires the semaphore if available instantly, otherwise returns false
		bool tryAcquire();
		// Signals the semaphore
		bool release();

	private:
		core_t* _core;

		semaphore(const semaphore&)				= delete;
		semaphore& operator=(const semaphore&)	= delete;
	};
}