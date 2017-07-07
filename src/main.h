#pragma once
#include "RLMath.h"
#include "SDL.h"

class CRenderer;

class CBaseScene {
public:
	virtual const char * GetName() const = 0;
	virtual void OnInit() = 0;
	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnInterface() = 0;
	virtual void OnRender(CRenderer& renderer) const = 0;
};

constexpr unsigned int WindowWidth = 1280;
constexpr unsigned int WindowHeight = 720;

extern SDL_Window* g_Window;

extern Vec2 g_MousePosition;
extern bool g_bMouseMovedThisFrame;
extern bool g_MouseButton[3];
extern bool g_MouseButtonDownThisFrame[3];
extern bool g_MouseButtonUpThisFrame[3];
