#include "pch.h"
#include "CInputManager.h"
#include "CRenderer.h"
#include "CHomingMissile.h"
#include "imgui.h"

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

void CHomingMissile::OnUpdate( const float dt, CInputManager& input ) {
	Vec2 mousePos = input.GetMousePosition();
	if ( mousePos.x > (WindowWidth - 320) ) {
		return;
	}

	for ( auto&& missile : m_Missiles ) {
		Vec2 diff = (mousePos - missile.pos);
		if ( diff.length() < missile.radius ) { continue; }

		missile.dir = diff.Normalize();
		missile.pos += missile.dir * (dt * m_MissileSpeed);
	}
}

void CHomingMissile::OnInterface() {
	if ( ImGui::Button( "Create Missile" ) ) {
		Missile missile;
		missile.pos = Vec2( static_cast<float>(rand() % WindowWidth), static_cast<float>(rand() % WindowHeight) );
		missile.radius = static_cast<float>(10 + (rand() % 20));
		m_Missiles.push_back( missile );
	}

	ImGui::SliderFloat( "Speed", &m_MissileSpeed, 0, 200 );
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
