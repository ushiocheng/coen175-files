#if !defined(GLOBAL_CONFIG_HPP)
#define GLOBAL_CONFIG_HPP

#define DEBUG
#ifdef DEBUG
#include <cassert>
#define VERBOSE_ERROR_MSG
#else
#define NDEBUG  // to suppress assert
#define assert(sth) /* (Suppressed by DEBUG Flag) Assert sth */
#endif


// PTR Size on target arch
// 4 => 32bit as of x86-32
#define ARCH_PTR_SIZE 4

#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define SIZEOF_CHAR 1

// Size of error type, doesn't matter but should be 0 or -1
#define SIZEOF_ERROR 0

// Define INT_MAX and INT_MIN
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif
#ifndef INT_MIN
#define INT_MIN -2147483648
#endif

#endif  // GLOBAL_CONFIG_HPP