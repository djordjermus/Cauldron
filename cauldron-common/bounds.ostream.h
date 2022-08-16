#include "bounds.h"
#include "vectors.ostream.h"
#include <ostream>
#pragma once
namespace cauldron::common {

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // B O U N D S   S T R E A M   O P E R A T O R S - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	template<class T>
	std::ostream& operator << (std::ostream& out, const cauldron::common::bounds2<T>& bounds) {
		out << bounds.from << " - " << bounds.to;
		return out;
	}
	template<class T>
	std::ostream& operator << (std::ostream& out, const cauldron::common::bounds3<T>& bounds) {
		out << bounds.from << " - " << bounds.to;
		return out;
	}

	template<class T>
	std::wostream& operator << (std::wostream& out, const cauldron::common::bounds2<T>& bounds) {
		out << bounds.from << L" - " << bounds.to;
		return out;
	}
	template<class T>
	std::wostream& operator << (std::wostream& out, const cauldron::common::bounds3<T>& bounds) {
		out << bounds.from << L" - " << bounds.to;
		return out;
	}
}
