#include "CHomingMissile.h"

#include "CRenderer.h"
#define IMGUI_DISABLE_TEST_WINDOWS
#include "imgui.h"
#undef IMGUI_DISABLE_TEST_WINDOWS

const char * CHomingMissile::GetName() const {
	return "Homing Missile";
}

void CHomingMissile::OnInit() {

}

void CHomingMissile::OnEnable() {

}

void CHomingMissile::OnDisable() {
	ClearMissiles();
}

void CHomingMissile::OnUpdate() {
	if ( g_MousePosition.x > (WindowWidth - 320) ) {
		return;
	}

	for ( auto&& missile : m_Missiles ) {
		Vec2 diff = (g_MousePosition - missile.pos);
		if ( diff.length() < missile.radius ) { continue; }

		missile.dir = diff.Normalize();
		missile.pos += missile.dir * m_MissileSpeed;
	}
}

void CHomingMissile::OnInterface() {
	if ( ImGui::Button( "Create Missile" ) ) {
		Missile missile;
		missile.pos = Vec2( static_cast<float>(rand() % WindowWidth), static_cast<float>(rand() % WindowHeight) );
		missile.dir = (g_MousePosition - missile.pos).Normalize();
		missile.radius = static_cast<float>(10 + (rand() % 20));
		m_Missiles.push_back( missile );
	}

	ImGui::SliderFloat( "Speed", &m_MissileSpeed, 0, 5 );
}

void CHomingMissile::OnRender( CRenderer& renderer ) const {
	for ( auto&& missile : m_Missiles ) {
		renderer.SetDrawColor( 1, 0, 1 );
		renderer.DrawCircle( Circle(missile.pos, missile.radius) );
		renderer.SetDrawColor( 0, 1, 0 );
		renderer.DrawLine( missile.pos, missile.pos + (missile.dir * 10) );
	}
}

void CHomingMissile::ClearMissiles() {
	m_Missiles.clear();
}
