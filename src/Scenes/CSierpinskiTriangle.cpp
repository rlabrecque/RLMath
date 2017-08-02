#include "pch.h"
#include "CInputManager.h"
#include "CRenderer.h"
#include "CSierpinskiTriangle.h"
#include "imgui.h"

const char * CSierpinskiTriangle::GetName() const {
	return "Sierpinski Triangle";
}

void CSierpinskiTriangle::OnInit() {
	m_point1 = Vec2( 400, 100 );
	m_point2 = Vec2( 700, 500 );
	m_point3 = Vec2( 100, 500 );

	m_Transform = Vec2::one;
	m_Scale = Vec2::one;
	m_Rot = 0;
	m_bAutomaticallyScale = true;
}

void CSierpinskiTriangle::OnEnable() {
}

void CSierpinskiTriangle::OnDisable() {
}

void CSierpinskiTriangle::OnUpdate( CInputManager& input ) {
	static float t = 0;
	/*Vec2 center = Vec2( (m_point1.x + m_point2.x + m_point3.x) / 3, (m_point1.y + m_point2.y + m_point3.y) / 3 );

	m_point1 -= center;
	m_point2 -= center;
	m_point3 -= center;

	Matrix4x4 test2 = Matrix4x4::identity;
	test2[{0, 0}] = RL_cos( theta );
	test2[{0, 1}] = -RL_sin( theta );
	test2[{1, 0}] = RL_sin( theta );
	test2[{2, 2}] = -RL_cos( theta );
	
	m_point1 = test2.MultiplyPoint2x3( m_point1 );
	m_point2 = test2.MultiplyPoint2x3( m_point2 );
	m_point3 = test2.MultiplyPoint2x3( m_point3 );

	m_point1 += center;
	m_point2 += center;
	m_point3 += center;*/

	if ( m_bAutomaticallyScale ) {
		const float s = 1 + RL_sin( t );
		m_Scale.x = s;
		//m_Scale.y = s;

		t += 0.02f;
	}
}

void CSierpinskiTriangle::OnInterface() {
	ImGui::BeginGroup();
	ImGui::PushItemWidth( -1 );
	float avail_width = ImGui::CalcItemWidth();
	ImGui::PopItemWidth();
	ImGui::PushItemWidth( (avail_width / 2) - ImGui::GetStyle().ItemInnerSpacing.x );
	ImGui::SliderFloat( "##Point1.x", &m_point1.data[0], 0.0f, static_cast<float>(WindowWidth) ); ImGui::SameLine();
	ImGui::SliderFloat( "##Point1.y", &m_point1.data[1], 0.0f, static_cast<float>(WindowHeight) );

	ImGui::SliderFloat( "##Point2.x", &m_point2.data[0], 0.0f, static_cast<float>(WindowWidth) ); ImGui::SameLine();
	ImGui::SliderFloat( "##Point2.y", &m_point2.data[1], 0.0f, static_cast<float>(WindowHeight) );

	ImGui::SliderFloat( "##Point3.x", &m_point3.data[0], 0.0f, static_cast<float>(WindowWidth) ); ImGui::SameLine();
	ImGui::SliderFloat( "##Point3.y", &m_point3.data[1], 0.0f, static_cast<float>(WindowHeight) );
	ImGui::PopItemWidth();
	ImGui::EndGroup();

	ImGui::Separator();

	ImGui::SliderFloat2( "Transform", m_Transform.data, -100.0f, 100.0f );
	ImGui::SliderFloat2( "Scale", m_Scale.data, 0.01f, 4.0f );
	ImGui::SliderAngle( "Rotation", &m_Rot );

	ImGui::Checkbox( "Auto Scale", &m_bAutomaticallyScale );
}

void CSierpinskiTriangle::OnRender( CRenderer& renderer ) const {
	Matrix4x4 m = Matrix4x4::Scale( m_Scale );

	Vec2 center = Vec2( (m_point1.x + m_point2.x + m_point3.x) / 3, (m_point1.y + m_point2.y + m_point3.y) / 3 );

	Vec2 newpoint1 = m_point1 - center;
	Vec2 newpoint2 = m_point2 - center;
	Vec2 newpoint3 = m_point3 - center;

	newpoint1 = m.MultiplyPoint2x3( newpoint1 );
	newpoint2 = m.MultiplyPoint2x3( newpoint2 );
	newpoint3 = m.MultiplyPoint2x3( newpoint3 );

	newpoint1 += center;
	newpoint2 += center;
	newpoint3 += center;
	
	DrawSierpinskiTriangleRecursive( renderer, newpoint1, newpoint2, newpoint3, 0 );

	renderer.SetDrawColor( 1, 1, 1 );
	renderer.DrawLine( newpoint1, newpoint2 );
	renderer.DrawLine( newpoint2, newpoint3 );
	renderer.DrawLine( newpoint3, newpoint1 );
}

void CSierpinskiTriangle::DrawSierpinskiTriangleRecursive( CRenderer& renderer, Vec2 A, Vec2 B, Vec2 C, int iteration ) const {
	if ( iteration == 6 ) { return; }
	++iteration;

	renderer.SetDrawColor( 0, 0, 0 );
	renderer.DrawTriangle( A, (A + B) / 2, (A + C) / 2 );
	renderer.DrawTriangle( B, (B + A) / 2, (B + C) / 2 );
	renderer.DrawTriangle( C, (C + A) / 2, (C + B) / 2 );

	renderer.SetDrawColor( 1, 1, 1 );
	renderer.DrawTriangle( (A + B) / 2, (A + C) / 2, (B + C) / 2 );

	DrawSierpinskiTriangleRecursive( renderer, A, (A + B) / 2, (A + C) / 2, iteration );
	DrawSierpinskiTriangleRecursive( renderer, B, (B + A) / 2, (B + C) / 2, iteration );
	DrawSierpinskiTriangleRecursive( renderer, C, (C + A) / 2, (C + B) / 2, iteration );
}
