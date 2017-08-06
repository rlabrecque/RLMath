#pragma once
#include "pch.h"

enum class EMouseButton : uint8_t {
	LEFT,
	RIGHT,
	MIDDLE,
	FOUR,
	FIVE,

	TOTAL
};

class CInputManager {
public:
	bool Init();
	void Shutdown();
	void ProcessEvent( SDL_Event& event );
	void OnUpdate( float dt );

	Vec2 GetMousePosition();
	Vec2 GetMouseWheel();
	bool MouseButtonIsDown( const EMouseButton button );
	bool MouseButtonWentDown( const EMouseButton button );
	bool MouseButtonWentUp( const EMouseButton button );

private:
	Vec2 m_MousePos = Vec2( 0, 0 );
	Vec2 m_MousePosPrev = Vec2( 0, 0 );
	Vec2 m_MouseWheel = Vec2( 0, 0 );
	bool m_MouseButtonState[(uint8_t)EMouseButton::TOTAL] = {};
	bool m_MouseButtonStatePrev[(uint8_t)EMouseButton::TOTAL] = {};
};
