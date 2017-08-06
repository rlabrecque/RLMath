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
		m_MouseButtonState[event.button.button - 1] = true;
	}
		break;
	case SDL_MOUSEWHEEL:
	{
		if ( event.wheel.y > 0 )
			m_MouseWheel.y = 1;
		if ( event.wheel.y < 0 )
			m_MouseWheel.y = -1;
		if ( event.wheel.x > 0 )
			m_MouseWheel.x = 1;
		if ( event.wheel.x < 0 )
			m_MouseWheel.x = -1;
	}
	break;
	case SDL_MOUSEBUTTONUP:
	{
		m_MouseButtonState[event.button.button - 1] = false;
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

void CInputManager::OnUpdate( float dt ) {
	memcpy( &m_MousePosPrev, &m_MousePos, sizeof( m_MousePos ) );
	memcpy( &m_MouseButtonStatePrev, &m_MouseButtonState, sizeof( m_MouseButtonState ) );
	m_MouseWheel = { 0, 0 };
}

Vec2 CInputManager::GetMousePosition() {
	return m_MousePos;
}

Vec2 CInputManager::GetMouseWheel() {
	return m_MouseWheel;
}

bool CInputManager::MouseButtonIsDown( const EMouseButton button ) {
	return m_MouseButtonState[(uint8_t)button];
}

bool CInputManager::MouseButtonWentDown( const EMouseButton button ) {
	return (m_MouseButtonState[(uint8_t)button] && !m_MouseButtonStatePrev[(uint8_t)button]);
}

bool CInputManager::MouseButtonWentUp( const EMouseButton button ) {
	return (!m_MouseButtonState[(uint8_t)button] && m_MouseButtonStatePrev[(uint8_t)button]);
}
