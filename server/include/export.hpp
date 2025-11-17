#pragma once

#if defined(_WIN32)
	#ifdef SERVER_LIBRARY_EXPORT
		#define SERVER_API __declspec(dllexport)
	#else
		#define SERVER_API __declspec(dllimport)
	#endif
#else
	#define SERVER_API
#endif

extern "C" {
	SERVER_API const char* process_json(const char* input_json);
}
