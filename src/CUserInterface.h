#pragma once
#include "pch.h"

class CInputManager;
class CSceneManager;

class CUserInterface {
public:
	bool Init();
	void Shutdown();
	bool ProcessEvent( SDL_Event& event );
	void RunFrame( float dt, CInputManager& inputManager, CSceneManager& sceneManager );
	void Render();
};
