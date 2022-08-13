#include "cauldron-common/primitives.h"
#pragma once
namespace cauldron::platform {
	class clock {
	public:
		static u64 getFrequency();
		static u64 getTimeStamp();
	};
}