#pragma once
#include "pch.h"

class CUserInterface;
class CSceneManager;

class CRenderer {
public:
	bool Init();
	void Shutdown();
	void RunFrame( const float dt, CSceneManager& sceneManager, CUserInterface& userInterface );

	void SetDrawColor( const Vec4 color );
	void SetDrawColor( const Vec3 color );
	void SetDrawColor( const float r, const float g, const float b );
	void DrawPoint( const Vec2 point );
	void DrawLine( const Vec2 start, const Vec2 end );
	void DrawLine( const Vec2 start, const Vec2 end, const Vec4 startColor, const Vec4 endColor );
	void DrawTriangle( const Vec2 topVertex, const Vec2 bottomRightVertex, const Vec2 bottomLeftVertex );
	void DrawTriangle( const Vec2 topVertex, const Vec2 bottomRightVertex, const Vec2 bottomLeftVertex, const Vec4 color1, const Vec4 color2, const Vec4 color3 );
	
	void DrawRay( const Ray ray );
	void DrawAABB( const AABB aabb );
	void DrawCircle( const Circle circle );

private:
	bool bInDrawing = false;
};
