#include "pch.h"
#include "CSceneManager.h"
#include "CSierpinskiTriangle.h"
#include "CGeometryPlayground.h"
#include "CHomingMissile.h"

bool CSceneManager::Init() {
	SDL_Log( "Initializing CSceneManager\n" );

	m_Scenes = {
		new CGeometryPlayground,
		new CSierpinskiTriangle,
		new CHomingMissile,
	};

	for ( auto&& scene : m_Scenes ) {
		scene->OnInit();
	}

	GetCurrentScene()->OnEnable();

	return true;
}

void CSceneManager::Shutdown() {
	for ( auto&& scene : m_Scenes ) {
		scene->OnDisable();
	}
}

std::array<CBaseScene*, NUMSCENES> CSceneManager::GetScenes() const {
	return m_Scenes;
}

CBaseScene* CSceneManager::GetCurrentScene() const {
	return m_Scenes[m_CurrentScene];
}

const unsigned int CSceneManager::GetCurrentSceneIndex() const {
	return m_CurrentScene;
}

const unsigned int CSceneManager::GetNumScenes() const {
	return m_Scenes.size();
}

void CSceneManager::ChangeScene( const unsigned int index ) {
	SDL_assert( index < m_Scenes.size() );
	SDL_assert( index != m_CurrentScene );

	m_Scenes[m_CurrentScene]->OnDisable();
	m_CurrentScene = index;
	m_Scenes[m_CurrentScene]->OnEnable();
}
