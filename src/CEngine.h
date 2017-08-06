#pragma once

#include "CInputManager.h"
#include "CRenderer.h"
#include "CUserInterface.h"
#include "CSceneManager.h"

class CEngine {
public:
	bool Init();
	void Shutdown();
	bool OnUpdate();

private:
	CInputManager m_InputManager;
	CRenderer m_Renderer;
	CUserInterface m_UserInterface;
	CSceneManager m_SceneManager;
};
