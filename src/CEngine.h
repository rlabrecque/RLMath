#pragma once

#include "CInputManager.h"
#include "CRenderer.h"
#include "CUserInterface.h"
#include "CSceneManager.h"

class CEngine {
public:
	bool Init();
	void Shutdown();
	void BeginUpdateLoop();

private:
	CInputManager m_pInputManager;
	CRenderer m_pRenderer;
	CUserInterface m_pUserInterface;
	CSceneManager m_pSceneManager;
};
