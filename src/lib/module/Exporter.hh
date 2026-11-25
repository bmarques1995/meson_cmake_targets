#pragma once

#define MESON_MOD_API

#ifdef MESON_MOD_WINDOWS
	#ifdef MESON_MOD_EXPORTS
		/* We are building this library */
		#define MESON_MOD_API __declspec(dllexport)
	#else
		/* We are using this library */
		#define MESON_MOD_API __declspec(dllimport)
	#endif
#endif
