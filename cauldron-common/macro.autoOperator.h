#pragma once
// Defines an inline bitwise AND operator for specified enum type
#define INLINE_BITWISE_AND(ENUM_T)\
inline static ENUM_T operator&(ENUM_T lhs, ENUM_T rhs) {\
	return (ENUM_T)((unsigned long long)lhs & (unsigned long long)rhs);\
}

// Defines an inline bitwise OR operator for specified enum type
#define INLINE_BITWISE_OR(ENUM_T)\
inline static ENUM_T operator|(ENUM_T lhs, ENUM_T rhs) {\
	return (ENUM_T)((unsigned long long)lhs | (unsigned long long)rhs);\
}

// Defines an inline bitwise XOR operator for specified enum type
#define INLINE_BITWISE_XOR(ENUM_T)\
inline static ENUM_T operator^(ENUM_T lhs, ENUM_T rhs) {\
	return (ENUM_T)((unsigned long long)lhs ^ (unsigned long long)rhs);\
}

// Defines an inline bitwise INVERT operator for specified enum type
#define INLINE_BITWISE_INVERT(ENUM_T)\
inline static ENUM_T operator~(ENUM_T rhs) {\
	return (ENUM_T)(~(unsigned long long)rhs);\
}