#pragma once
#pragma message("Creating precompiled header.\n")

#ifdef _DEBUG
#define RL_DEBUG 1
#endif

#ifdef RL_DEBUG
#define RL_DEBUGBREAK() __debugbreak()
#else
#define RL_DEBUGBREAK() ((void)0)
#endif

#define SAFE_DELETE(__ptr__) if(__ptr__ != nullptr) delete __ptr__, __ptr__ = nullptr
#define SAFE_DELETE_ARRAY(__ptr__) if(__ptr__ != nullptr) delete[] __ptr__, __ptr__ = nullptr
#define SAFE_SHUTDOWN(__ptr__) if(__ptr__ != nullptr) __ptr__->Shutdown(); delete __ptr__, __ptr__ = nullptr
#define SAFE_RELEASE(__ptr__) if(__ptr__ != nullptr) __ptr__->Release(), __ptr__ = nullptr

#include <stdint.h>
#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "SDL.h"
#include "RLMath.h"


constexpr unsigned int WindowWidth = 1280;
constexpr unsigned int WindowHeight = 720;

extern SDL_Window* g_Window;
