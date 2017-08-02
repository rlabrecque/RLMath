#pragma once
#include "pch.h"

class CUserInterface;
class CSceneManager;

class CRenderer {
public:
	bool Init();
	void Shutdown();
	void RunFrame( CSceneManager& sceneManager, CUserInterface& userInterface  );

	void SetDrawColor( Vec4 color );
	void SetDrawColor( Vec3 color );
	void SetDrawColor( unsigned char r, unsigned char g, unsigned char b );
	void DrawPoint( Vec2 point );
	void DrawLine( Vec2 start, Vec2 end );
	void DrawTriangle( Vec2 topVertex, Vec2 bottomRightVertex, Vec2 bottomLeftVertex );
	
	void DrawRay( Ray ray );
	void DrawAABB( AABB aabb );
	void DrawCircle( Circle circle );

private:
	bool bInDrawing = false;
};
