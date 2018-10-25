#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
	#define MANGO_SYS_WINDOWS

	// Defined to disable <windows.h> from defining the min/max macros (SDL has issues with this)
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

#elif defined(__LINUX__)
	#define MANGO_SYS_LINUX
#elif defined(__APPLE__)
	#define MANGO_SYS_MACOS
#endif

#ifndef MANGO_STATIC_BUILD

	#ifdef MANGO_SYS_WINDOWS

		#ifdef MANGO_NONCLIENT_BUILD
			#define MANGO_API __declspec(dllexport)
		#else
			#define MANGO_API __declspec(dllimport)
		#endif

		// Visual c++ compiler warning C4251 disable
		#ifdef _MSC_VER
			#pragma warning(disable : 4251)
		#endif

	#else // Linux / OSX

		// Check GNUC >= 4 (for linux development)
		#ifdef __GNUC__ >= 4

			#define MANGO_API __attribute__ ((__visibility__("default")))
		#else

			#define MANGO_API MANGO_API
		#endif

	#endif

#else
	#define MANGO_API
#endif


// DEBUG 
#if defined(MANGO_ASSERTIONS_ENABLED) // Used to strip assertions later 
#define MANGO_TRAP(expr) \
if (expr) { } \
else \
{ \
do { \
_CrtDbgReport( \
_CRT_ASSERT, __FILE__, __LINE__, #expr, NULL); \
_CrtDbgBreak(); \
} while (1); \
}
#else
#define MANGO_TRAP(expr) // do nothing
#endif


#endif