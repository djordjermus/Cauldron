#include "primitives.h"
#pragma once
namespace cauldron::common {

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // R A N D O M   N U M B E R   G E N E R A T O R - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// random class used for generating random numbers - contains a seed
	class random final {
	public:
		// Starting seed is initialized to time(0)
		random();
		// Starting seed is initialized to given value
		random(u64 seed);

		// Generates a pseudo-random unsigned 64 bit integer in range [from, from + range)
		u64 range(u64 from, u64 range);
		// Generates a pseudo-random unsigned 64 bit integer in range [0, range)
		u64 range(u64 range);
		// Generates a pseudo-random signed 64 bit integer in range [from, from + range)
		i64 range(i64 from, i64 range);
		// Generates a pseudo-random signed 64 bit integer in range [0, range)
		i64 range(i64 range);
		// Generates a pseudo-random double in range [from, from + range)
		f64 range(f64 from, f64 range);
		// Generates a pseudo-random double in range [0, range)
		f64 range(f64 range);

		// Sets the new seed
		void setSeed(u64 seed);

	private:
		inline u64 generate();

		u64 _seed;
	};
}