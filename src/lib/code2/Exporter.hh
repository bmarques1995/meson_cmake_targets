#pragma once

#define MESON_LOG_API

#ifdef MESON_LOG_SHARED
	#ifdef MESON_LOG_WINDOWS
		#ifdef MESON_LOG_EXPORTS
			/* We are building this library */
			#define MESON_LOG_API __declspec(dllexport)
		#else
			/* We are using this library */
			#define MESON_LOG_API __declspec(dllimport)
		#endif
	#endif
#endif