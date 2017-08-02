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
	void BeginFrame();

	Vec2 GetMousePosition();
	bool MouseButtonIsDown( const EMouseButton button );
	bool MouseButtonWentDown( const EMouseButton button );
	bool MouseButtonWentUp( const EMouseButton button );

private:
	Vec2 m_MousePos = Vec2( 0, 0 );
	Vec2 m_MousePosPrev = Vec2( 0, 0 );
	bool m_MouseState[(uint8_t)EMouseButton::TOTAL] = {};
	bool m_MouseStatePrev[(uint8_t)EMouseButton::TOTAL] = {};
};
