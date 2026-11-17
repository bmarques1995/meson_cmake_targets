#pragma once

#define MESON_LIB_API

#ifdef MESON_LIB_SHARED
    #ifdef MESON_LIB_WINDOWS
        #ifdef MESON_LIB_EXPORTS
            /* We are building this library */
            #define MESON_LIB_API __declspec(dllexport)
        #else
            /* We are using this library */
            #define MESON_LIB_API __declspec(dllimport)
        #endif
    #endif
#endif
