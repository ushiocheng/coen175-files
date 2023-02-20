#if !defined(GLOBAL_CONFIG_HPP)
#define GLOBAL_CONFIG_HPP

#define DEBUG
#ifdef DEBUG
#define VERBOSE_ERROR_MSG
#else
#define NDEBUG  // to suppress assert
#endif

// PTR Size on target arch
// 4 => 32bit as of x86-32
#define ARCH_PTR_SIZE 4

#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define SIZEOF_CHAR 1

// Size of error type, doesn't matter but should be 0 or -1
#define SIZEOF_ERROR 0

#endif  // GLOBAL_CONFIG_HPP