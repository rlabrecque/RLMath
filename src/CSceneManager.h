#pragma once
#include "pch.h"
#include "CBaseScene.h"

#include <array>

constexpr unsigned int NUMSCENES = 5;

class CSceneManager {
public:
	bool Init();
	void Shutdown();

	void ChangeScene( const unsigned int index );

	std::array<CBaseScene*, NUMSCENES> GetScenes() const;
	CBaseScene* GetCurrentScene() const;
	const unsigned int GetCurrentSceneIndex() const;
	const unsigned int GetNumScenes() const;

private:
	unsigned int m_CurrentScene = 0;
	std::array<CBaseScene*, NUMSCENES> m_Scenes;
};
