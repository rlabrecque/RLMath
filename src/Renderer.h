#pragma once
#include "main.h"

int Renderer_Init();
void Renderer_Shutdown();
void Renderer_RunFrame();

void Renderer_SetDrawColor( Vec4 color );
void Renderer_DrawPoint( Vec2 point );
void Renderer_DrawLine( Vec2 start, Vec2 end );
void Renderer_DrawTriangle( Vec2 topVertex, Vec2 bottomRightVertex, Vec2 bottomLeftVertex );
void Renderer_DrawRay( Ray ray );
