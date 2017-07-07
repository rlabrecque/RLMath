#pragma once
#include "main.h"
#include <array>

class CSceneManager {
public:
	bool Init();
	void Shutdown();

	void ChangeScene( const unsigned int index );

	std::array<CBaseScene*, 2> GetScenes() const;
	CBaseScene* GetCurrentScene() const;
	const unsigned int GetCurrentSceneIndex() const;
	const unsigned int GetNumScenes() const;

private:
	unsigned int m_CurrentScene;
	std::array<CBaseScene*, 2> m_Scenes;
};
