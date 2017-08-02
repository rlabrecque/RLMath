#include "pch.h"
#include "CInputManager.h"

bool CInputManager::Init() {
	SDL_Log( "Initializing CInputManager\n" );
	
	return true;
}

void CInputManager::Shutdown() {

}

void CInputManager::ProcessEvent( SDL_Event& event ) {
	switch ( event.type ) {
	case SDL_MOUSEBUTTONDOWN:
	{
		m_MouseState[event.button.button - 1] = true;
	}
		break;
	case SDL_MOUSEBUTTONUP:
	{
		m_MouseState[event.button.button - 1] = false;
	}
		break;
	case SDL_MOUSEMOTION:
	{
		int x, y;
		SDL_GetMouseState( &x, &y );
		m_MousePos.x = (float)x;
		m_MousePos.y = (float)y;
	}
		break;
	}

	const uint8_t* keyboardState = SDL_GetKeyboardState( NULL );
}

void CInputManager::BeginFrame() {
	memcpy( &m_MousePosPrev, &m_MousePos, sizeof( m_MousePos ) );
	memcpy( &m_MouseStatePrev, &m_MouseState, sizeof( m_MouseState ) );
}

Vec2 CInputManager::GetMousePosition() {
	return m_MousePos;
}

bool CInputManager::MouseButtonIsDown( const EMouseButton button ) {
	return m_MouseState[(uint8_t)button];
}

bool CInputManager::MouseButtonWentDown( const EMouseButton button ) {
	return (m_MouseState[(uint8_t)button] && !m_MouseStatePrev[(uint8_t)button]);
}

bool CInputManager::MouseButtonWentUp( const EMouseButton button ) {
	return (!m_MouseState[(uint8_t)button] && m_MouseStatePrev[(uint8_t)button]);
}
