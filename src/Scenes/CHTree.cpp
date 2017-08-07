#include "pch.h"
#include "CInputManager.h"
#include "CRenderer.h"
#include "CHTree.h"
#include "imgui.h"

const char *CHTree::GetName() const {
	return "H Tree";
}

void CHTree::OnInit() {
}

void CHTree::OnEnable() {

}

void CHTree::OnDisable() {
}

void CHTree::OnUpdate( const float dt, CInputManager& input ) {
}

void CHTree::OnInterface() {
	ImGui::SliderInt( "Iterations", &m_Iterations, 1, 8 );
}

void Render( CRenderer& renderer, Vec2 center, int level, float length ) {
	if ( level == 0 ) { return; }
	level--;

	length /= RL_sqrt( 2 );
	Vec2 start = Vec2( center.x - (length / 2), center.y );
	Vec2 end = Vec2( center.x + (length / 2), center.y );

	renderer.DrawLine( start, end );

	length /= RL_sqrt( 2 );
	Vec2 leftTop = Vec2( start.x, center.y - length / 2 );
	Vec2 leftBottom = Vec2( start.x, center.y + length / 2 );

	Vec2 rightTop = Vec2( end.x, center.y - length / 2 );
	Vec2 rightBottom = Vec2( end.x, center.y + length / 2 );

	renderer.DrawLine( leftTop, leftBottom );
	renderer.DrawLine( rightTop, rightBottom );

	Render( renderer, leftTop, level, length );
	Render( renderer, leftBottom, level, length );
	Render( renderer, rightTop, level, length );
	Render( renderer, rightBottom, level, length );
}

void CHTree::OnRender( CRenderer& renderer ) const {
	Vec2 center = Vec2( WindowWidth / 2, WindowHeight / 2 );

	Render( renderer, center, m_Iterations, WindowWidth / 2 );
}
