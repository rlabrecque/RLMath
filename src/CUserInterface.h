#pragma once
#include "pch.h"

class CSceneManager;

class CUserInterface {
public:
	bool Init();
	void Shutdown();
	void ProcessEvent( SDL_Event& event );
	void RunFrame( CSceneManager& sceneManager );
	void Render();
};
