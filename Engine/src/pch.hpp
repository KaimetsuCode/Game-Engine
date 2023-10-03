#pragma once

// std libs
#include <iostream>
#include <map>
#include <vector>


// 3rd party libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

// Export API

#ifdef KAIM_EXPORT
    #ifdef _MSC_VER
        #define KAIM_API __declspec(dllexport)
    #else
        #define KAIM_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define KAIM_API __declspec(dllimport)
    #else
        #define KAIM_API
    #endif
#endif

// Loggin System

#if defined(_DEBUG)
    #define KAIM_LOG(level, message, ...) \
    fprintf(stderr, "[%s] ", level); \
    fprintf(stderr, message, ##__VA_ARGS__); \
    fprintf(stderr, "\n");

    #define WARNING(message, ...) KAIM_LOG("WARNING", message, ##__VA_ARGS__)
    #define ERROR(message, ...) KAIM_LOG("ERROR", message, ##__VA_ARGS__)
    #define INFO(message, ...) KAIM_LOG("INFO", message, ##__VA_ARGS__)
#else
    #define WARNING
    #define ERROR
    #define INFO
#endif


// Function inlining
#if defined(__clang__) || defined(__gcc__)
    #define KAIM_INLINE __attribute__((always_inline)) inline
    #define KAIM_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
    #define KAIM_INLINE __forceinline
    #define KAIM_NOINLINE __declspec(noinline)
#else
    #define KAIM_INLINE inline
    #define KAIM_NOINLINE
#endif
