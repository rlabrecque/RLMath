#include "pch.h"
#include "CInputManager.h"
#include "CRenderer.h"
#include "CGeometryPlayground.h"

#include "imgui.h"

const char *CGeometryPlayground::GetName() const {
	return "Geometry Playground";
}

void CGeometryPlayground::OnInit() {

}

void CGeometryPlayground::OnEnable() {

}

void CGeometryPlayground::OnDisable() {
	ClearGeometry();
}

void CGeometryPlayground::OnUpdate( const float dt, CInputManager& input ) {
	m_CurrPos = input.GetMousePosition();

	if ( m_CurrPos.x > (WindowWidth - 320) ) {
		return;
	}

	if ( input.MouseButtonWentDown( EMouseButton::LEFT ) ) {
		m_StartPos = m_CurrPos;
	}

	if ( input.MouseButtonWentUp( EMouseButton::LEFT ) ) {
		GeometryEntity entity;
		entity.type = m_InsertMode;
		entity.color = m_DrawColor;

		switch ( m_InsertMode ) {
		case k_EGeometry_Point:
			entity.point = m_CurrPos;
			break;
		case k_EGeometry_Ray:
			entity.ray = Ray( m_StartPos, m_CurrPos - m_StartPos );
			break;
		case k_EGeometry_AABB:
			entity.aabb = AABB::FromMinsMaxs( m_StartPos, m_CurrPos );
			break;
		case k_EGeometry_Circle:
			entity.circle = Circle( m_StartPos, (m_StartPos - m_CurrPos).length() );
			break;
		}

		m_GeometryEntities.emplace_back( entity );
		m_StartPos = Vec2::zero;
	}
}

void CGeometryPlayground::OnInterface() {
	ImGui::ColorEdit3( "Draw Color", m_DrawColor.data );

	if ( ImGui::Button( "Clear Geometry" ) ) {
		ClearGeometry();
	}

	ImGui::RadioButton( "Point", (int*)&m_InsertMode, k_EGeometry_Point ); ImGui::SameLine();
	ImGui::RadioButton( "Ray", (int*)&m_InsertMode, k_EGeometry_Ray ); ImGui::SameLine();
	ImGui::RadioButton( "AABB", (int*)&m_InsertMode, k_EGeometry_AABB ); ImGui::SameLine();
	ImGui::RadioButton( "Circle", (int*)&m_InsertMode, k_EGeometry_Circle );

	ImGui::Separator();

	ImGui::RadioButton( "Collision", (int*)&m_TestMode, k_EGeometryTestMode_Collision ); ImGui::SameLine();
	ImGui::RadioButton( "Distance", (int*)&m_TestMode, k_EGeometryTestMode_Distance );

	ImGui::Separator();

	ImGui::CheckboxFlags( "Test Against Points", (unsigned int*)&m_TestGeometry, (unsigned int)k_EGeometry_Point );
	ImGui::CheckboxFlags( "Test Against Rays", (unsigned int*)&m_TestGeometry, (unsigned int)k_EGeometry_Ray );
	ImGui::CheckboxFlags( "Test Against AABBs", (unsigned int*)&m_TestGeometry, (unsigned int)k_EGeometry_AABB );
	ImGui::CheckboxFlags( "Test Against Circles", (unsigned int*)&m_TestGeometry, (unsigned int)k_EGeometry_Circle );

	ImGui::Separator();

	if ( m_StartPos != Vec2::zero ) {
		ImGui::Text( "StartPos: %s", m_StartPos.ToString() );
	}
	else {
		ImGui::Text( "StartPos: " );
	}

	ImGui::PushItemWidth( -1 );
	ImGui::ListBoxHeader( "##empty" );
	for ( unsigned int i = 0; i < m_GeometryEntities.size(); ++i ) {
		auto&& entity = m_GeometryEntities[i];
		bool selected = false;
		switch ( entity.type ) {
		case k_EGeometry_Point:
			selected = ImGui::Selectable( entity.point.ToString(), false );
			break;
		case k_EGeometry_Ray:
			selected = ImGui::Selectable( entity.ray.ToString(), false );
			break;
		case k_EGeometry_AABB:
			selected = ImGui::Selectable( entity.aabb.ToString(), false );
			break;
		case k_EGeometry_Circle:
			selected = ImGui::Selectable( entity.circle.ToString(), false );
			break;
		}

		if ( selected ) {
			m_GeometryEntities.erase( m_GeometryEntities.begin() + i );
		}
	}
	ImGui::ListBoxFooter();
}

void CGeometryPlayground::OnRender( CRenderer& renderer ) const {
	if ( m_StartPos == Vec2::zero ) {
		for ( auto&& entity : m_GeometryEntities ) {
			renderer.SetDrawColor( entity.color );

			switch ( entity.type ) {
			case k_EGeometry_Point:
				renderer.DrawPoint( entity.point );
				break;
			case k_EGeometry_Ray:
				renderer.DrawRay( entity.ray );
				break;
			case k_EGeometry_AABB:
				renderer.DrawAABB( entity.aabb );
				break;
			case k_EGeometry_Circle:
				renderer.DrawCircle( entity.circle );
				break;
			}
		}
	}
	else {
		switch ( m_InsertMode ) {
		case k_EGeometry_Point:
			RenderInsertPoint(renderer, m_CurrPos );
			break;
		case k_EGeometry_Ray:
			RenderInsertRay( renderer, Ray( m_StartPos, m_CurrPos - m_StartPos ) );
			break;
		case k_EGeometry_AABB:
			RenderInsertAABB( renderer, AABB::FromMinsMaxs( m_StartPos, m_CurrPos ) );
			break;
		case k_EGeometry_Circle:
			RenderInsertCircle( renderer, Circle( m_StartPos, (m_StartPos - m_CurrPos).length() ) );
			break;
		}
	}
}

void CGeometryPlayground::RenderInsertPoint( CRenderer& renderer, const Vec2 point ) const {
	for ( auto&& entity : m_GeometryEntities ) {
		switch ( entity.type ) {
		case k_EGeometry_Point:
			renderer.SetDrawColor( entity.color );
			renderer.DrawPoint( entity.point );

			if ( (m_TestGeometry & k_EGeometry_Point) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( point, entity.point );
			}
			break;
		case k_EGeometry_Ray:
			if ( (m_TestGeometry & k_EGeometry_Ray) && m_TestMode == k_EGeometryTestMode_Collision && RayIntersectsPoint( entity.ray, point ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawRay( entity.ray );

			if ( (m_TestGeometry & k_EGeometry_Ray) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( point, entity.ray.GetClosestPoint( point ) );
			}
			break;
		case k_EGeometry_AABB:
			if ( (m_TestGeometry & k_EGeometry_AABB) && m_TestMode == k_EGeometryTestMode_Collision && AABBContainsPoint( entity.aabb, point) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawAABB( entity.aabb );

			if ( (m_TestGeometry & k_EGeometry_AABB) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( point, entity.aabb.GetClosestPoint( point ) );
			}
			break;
		case k_EGeometry_Circle:
			if ( (m_TestGeometry & k_EGeometry_Circle) && m_TestMode == k_EGeometryTestMode_Collision && CircleContainsPoint( entity.circle, point ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawCircle( entity.circle);

			if ( (m_TestGeometry & k_EGeometry_Circle) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( point, entity.circle.GetClosestPoint( point ) );
			}
			break;
		}
	}

	renderer.SetDrawColor( m_DrawColor );
	renderer.DrawPoint( point );
}

void CGeometryPlayground::RenderInsertRay( CRenderer& renderer, const Ray ray ) const {
	for ( auto&& entity : m_GeometryEntities ) {
		switch ( entity.type ) {
		case k_EGeometry_Point:
			if ( (m_TestGeometry & k_EGeometry_Ray) && m_TestMode == k_EGeometryTestMode_Collision && RayIntersectsPoint( ray, entity.point ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawPoint( entity.point );

			if ( (m_TestGeometry & k_EGeometry_Point) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( entity.point, ray.GetClosestPoint( entity.point ) );
			}
			break;
		case k_EGeometry_Ray:
			if ( (m_TestGeometry & k_EGeometry_Ray) && m_TestMode == k_EGeometryTestMode_Collision && RayIntersectsRay( ray, entity.ray ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawRay( entity.ray );
			break;
		case k_EGeometry_AABB:
			if ( (m_TestGeometry & k_EGeometry_AABB) && m_TestMode == k_EGeometryTestMode_Collision && RayIntersectsAABB( ray, entity.aabb ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawAABB( entity.aabb );
			break;
		case k_EGeometry_Circle:
			renderer.SetDrawColor( entity.color );
			renderer.DrawCircle( entity.circle );
			break;
		}
	}
	
	renderer.SetDrawColor( m_DrawColor );
	renderer.DrawRay( ray );
}

void CGeometryPlayground::RenderInsertAABB( CRenderer& renderer, const AABB aabb ) const {
	for ( auto&& entity : m_GeometryEntities ) {
		switch ( entity.type ) {
		case k_EGeometry_Point:
			if ( (m_TestGeometry & k_EGeometry_Point) && m_TestMode == k_EGeometryTestMode_Collision && AABBContainsPoint( aabb, entity.point ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawPoint( entity.point );

			if ( (m_TestGeometry & k_EGeometry_Point) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( entity.point, aabb.GetClosestPoint( entity.point ) );
			}
			break;
		case k_EGeometry_Ray:
			if ( (m_TestGeometry & k_EGeometry_Ray) && m_TestMode == k_EGeometryTestMode_Collision && RayIntersectsAABB( entity.ray, aabb ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawRay( entity.ray );
			break;
		case k_EGeometry_AABB:
			if ( (m_TestGeometry & k_EGeometry_AABB) && m_TestMode == k_EGeometryTestMode_Collision && AABBIntersectsAABB( aabb, entity.aabb ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawAABB( entity.aabb );

			if ( (m_TestGeometry & k_EGeometry_AABB) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( entity.aabb.origin, aabb.GetClosestPoint( entity.aabb ) );
			}
			break;
		case k_EGeometry_Circle:
			if ( (m_TestGeometry & k_EGeometry_Circle) && m_TestMode == k_EGeometryTestMode_Collision && AABBIntersectsCircle( aabb, entity.circle ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawCircle( entity.circle );
			break;
		}
	}
	
	renderer.SetDrawColor( m_DrawColor );
	renderer.DrawAABB( aabb );
}

void CGeometryPlayground::RenderInsertCircle( CRenderer& renderer, const Circle circle ) const {
	for ( auto&& entity : m_GeometryEntities ) {
		switch ( entity.type ) {
		case k_EGeometry_Point:
			if ( (m_TestGeometry & k_EGeometry_Point) && m_TestMode == k_EGeometryTestMode_Collision && CircleContainsPoint( circle, entity.point ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawPoint( entity.point );

			if ( (m_TestGeometry & k_EGeometry_Point) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( entity.point, circle.GetClosestPoint( entity.point ) );
			}
			break;
		case k_EGeometry_Ray:
			renderer.SetDrawColor( entity.color );
			renderer.DrawRay( entity.ray );
			break;
		case k_EGeometry_AABB:
			if ( (m_TestGeometry & k_EGeometry_AABB) && m_TestMode == k_EGeometryTestMode_Collision && AABBIntersectsCircle( entity.aabb, circle ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawAABB( entity.aabb );

			/*if ( (m_TestGeometry & k_EGeometry_AABB) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( entity.aabb.GetClosestPoint( circle ), circle.GetClosestPoint( aabb ) );
			}*/
			break;
		case k_EGeometry_Circle:
			if ( (m_TestGeometry & k_EGeometry_Circle) && m_TestMode == k_EGeometryTestMode_Collision && CircleIntersectsCircle( circle, entity.circle ) ) {
				renderer.SetDrawColor( 1, 0, 0 );
			}
			else {
				renderer.SetDrawColor( entity.color );
			}

			renderer.DrawCircle( entity.circle );

			if ( (m_TestGeometry & k_EGeometry_Circle) && m_TestMode == k_EGeometryTestMode_Distance ) {
				renderer.DrawLine( entity.circle.GetClosestPoint( circle ), circle.GetClosestPoint( entity.circle ) );
			}
			break;
		}
	}

	renderer.SetDrawColor( m_DrawColor );
	renderer.DrawCircle( circle );
}

void CGeometryPlayground::ClearGeometry() {
	m_GeometryEntities.clear();
	m_StartPos = Vec2::zero;
}
