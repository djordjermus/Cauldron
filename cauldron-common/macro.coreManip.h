#pragma once
// Creates an inline const function that returns core ponter
// CORE_T - core type
// VAR_ID - member variable containing the CORE_T pointer to core
#define INLINE_CORE_GET(CORE_T, VAR_ID)\
inline CORE_T* getCore() const { return VAR_ID; }

// Creates an inline function that sets the core pointer
// CORE_T - core type
// VAR_ID - member variable containing the CORE_T pointer to core
#define INLINE_CORE_SET(CORE_T, VAR_ID)\
inline CORE_T* setCore(CORE_T* new_core) { CORE_T* ret = VAR_ID; VAR_ID = new_core; return ret; }

// Creates inline const operators for comparing instances of T by core
// T - core containing type
// CORE_T - core type
// VAR_ID - member variable containing the CORE_T pointer to core
#define INLINE_CORE_CMP(T, CORE_T, VAR_ID)\
inline bool operator==(const T& other) const { return VAR_ID == other.VAR_ID; }\
inline bool operator!=(const T& other) const { return VAR_ID != other.VAR_ID; }

// Creates a move constructor and move assignemnt operator for given type T based on core
// T - core containing type
// CORE_T - core type
// VAR_ID - member variable containing the CORE_T pointer to core
#define INLINE_CORE_MOVE(T, CORE_T, VAR_ID)\
inline T(T&& move) : VAR_ID(move.VAR_ID) { move.VAR_ID = nullptr; }\
inline T& operator=(T&& move) {\
	CORE_T* temp = VAR_ID; VAR_ID = move.VAR_ID; move.VAR_ID = temp; return *this;\
}\

// Creates a move constructor and move assignemnt operator for given type T based on core
// T - core containing type
// CORE_T - core type
// VAR_ID - member variable containing the CORE_T pointer to core
#define INLINE_CORE_SWAP(T, CORE_T, VAR_ID)\
inline void swap(T& other) { CORE_T* temp = VAR_ID; VAR_ID = other.VAR_ID; other.VAR_ID = temp; }





