#pragma once
#include "RLMath.h"
#include "SDL.h"

#include <unordered_map>

constexpr int WindowWidth = 1280;
constexpr int WindowHeight = 720;

enum EGeometryInsertMode {
	k_EGeometryInsertMode_Point,
	k_EGeometryInsertMode_Ray,
	k_EGeometryInsertMode_Plane,
	k_EGeometryInsertMode_Rect,
	k_EGeometryInsertMode_Circle,
};

class BaseScene {
public:
	virtual void Init();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void Update();
	virtual void Render();
};

void ClearGeometry();

extern SDL_Window* g_Window;
extern std::unordered_map<Vec2, Vec4> points;
extern std::unordered_map<Ray, Vec4> rays;
extern EGeometryInsertMode mode;

extern bool bPlacingRay;
extern Vec2 RayPosition;
extern Vec2 MousePosition;

extern bool bDrawSierpinski;
