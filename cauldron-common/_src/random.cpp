#include "../random.h"
#include <time.h>
#include <math.h>
namespace cauldron::common {
	static constexpr u64 x = 12;
	static constexpr u64 y = 25;
	static constexpr u64 z = 27;
	static constexpr u64 m = 2685821657736338717ULL;

	random::random() :
		_seed(time(0)) {}
	random::random(u64 seed) :
		_seed(seed) {}

	u64 random::range(u64 from, u64 range) {
		return from + (generate() % range);
	}
	u64 random::range(u64 range) {
		return random::range(0ull, range);
	}
	i64 random::range(i64 from, i64 range) {
		return from + (generate() % range);
	}
	i64 random::range(i64 range) {
		return random::range(0ll, range);
	}
	f64 random::range(f64 from, f64 range) {
		return from + fmod(generate() * 0.0000000000000001, range);
	}
	f64 random::range(f64 range) {
		return random::range(0.0, range);
	}

	void random::setSeed(u64 seed) {
		_seed = seed;
	}

	inline u64 random::generate() {
		u64 ret = _seed;
		ret ^= ret << x;
		ret ^= ret >> y;
		ret ^= ret << z;
		return _seed = ret;
	}
}