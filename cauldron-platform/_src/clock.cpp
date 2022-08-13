#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include "../clock.h"

namespace cauldron::platform {
	inline static u64 getClockFrequency();

	u64 clock::getFrequency() {
		static u64 ret = getClockFrequency();
		return ret;
	}
	u64 clock::getTimeStamp() {
		u64 ret = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&ret);
		return ret;
	}



	inline static u64 getClockFrequency() {
		u64 ret = 0;
		QueryPerformanceFrequency((LARGE_INTEGER*)&ret);
		return ret;
	}
}
#endif
