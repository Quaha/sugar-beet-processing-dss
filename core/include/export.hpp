#pragma once

#if defined(_WIN32)
	#ifdef CORE_LIBRARY_EXPORT
		#define DLL_API __declspec(dllexport)
	#else
		#define DLL_API __declspec(dllimport)
	#endif
#else
	#define DLL_API
#endif

extern "C" {
	DLL_API const char* ProcessJSON(const char* input_json);
}
