#pragma once
#include "main.h"

extern Vec4 g_ClearColor;
extern Vec4 g_DrawColor;
extern Vec4 g_LineDrawColor;

void Interface_Init();
void Interface_Shutdown();
void Interface_ProcessEvent( SDL_Event* event );
void Interface_RunFrame();
void Interface_Draw();
