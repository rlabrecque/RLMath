#include "CGeometryPlayground.h"

#include "CRenderer.h"
#define IMGUI_DISABLE_TEST_WINDOWS
#include "imgui.h"
#undef IMGUI_DISABLE_TEST_WINDOWS

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

void CGeometryPlayground::OnUpdate() {
	if ( g_MousePosition.x > (WindowWidth - 320) ) {
		return;
	}

	if ( g_MouseButtonDownThisFrame[0] ) {
		m_StartPos = g_MousePosition;
	}

	if ( g_MouseButtonUpThisFrame[0] ) {
		printf( "%s\n", m_StartPos.ToString() );
		switch ( m_InsertMode ) {
		case k_EGeometryInsertMode_Point:
			m_PointsDict[g_MousePosition] = { m_DrawColor, false };
			break;
		case k_EGeometryInsertMode_Ray:
			m_RaysDict[Ray( m_StartPos, (m_StartPos + ((g_MousePosition - m_StartPos).normalized() * 10000)) )] = { m_DrawColor, false };
			break;
		case k_EGeometryInsertMode_AABB:
			m_AABBsDict[AABB::FromMinsMaxs( m_StartPos, g_MousePosition )] = { m_DrawColor, false };
			break;
		case k_EGeometryInsertMode_Circle:
			m_CirclesDict[Circle( m_StartPos, (m_StartPos - g_MousePosition).magnitude())] = { m_DrawColor, false };
			break;
		}

		m_StartPos = Vec2::zero;
	}
}

void CGeometryPlayground::OnInterface() {
	ImGui::ColorEdit3( "Draw Color", m_DrawColor.data );

	if ( ImGui::Button( "Clear Geometry" ) ) {
		ClearGeometry();
	}

	ImGui::RadioButton( "Point", (int*)&m_InsertMode, k_EGeometryInsertMode_Point ); ImGui::SameLine();
	ImGui::RadioButton( "Ray", (int*)&m_InsertMode, k_EGeometryInsertMode_Ray ); ImGui::SameLine();
	ImGui::RadioButton( "AABB", (int*)&m_InsertMode, k_EGeometryInsertMode_AABB ); ImGui::SameLine();
	ImGui::RadioButton( "Circle", (int*)&m_InsertMode, k_EGeometryInsertMode_Circle );

	ImGui::Separator();

	ImGui::RadioButton( "Collision", (int*)&m_TestMode, k_EGeometryTestMode_Collision ); ImGui::SameLine();
	ImGui::RadioButton( "Distance", (int*)&m_TestMode, k_EGeometryTestMode_Distance );

	ImGui::Separator();

	ImGui::CheckboxFlags( "Test Against Points", (unsigned int*)&m_TestGeometry, (unsigned int)k_EGeometryInsertMode_Point );
	ImGui::CheckboxFlags( "Test Against Rays", (unsigned int*)&m_TestGeometry, (unsigned int)k_EGeometryInsertMode_Ray );
	ImGui::CheckboxFlags( "Test Against AABBs", (unsigned int*)&m_TestGeometry, (unsigned int)k_EGeometryInsertMode_AABB );
	ImGui::CheckboxFlags( "Test Against Circles", (unsigned int*)&m_TestGeometry, (unsigned int)k_EGeometryInsertMode_Circle );

	ImGui::Separator();

	if ( m_StartPos != Vec2::zero ) {
		ImGui::Text( "StartPos: %s", m_StartPos.ToString() );
	}
	else {
		ImGui::Text( "StartPos: " );
	}

	ImGui::PushItemWidth( -1 );
	ImGui::ListBoxHeader( "##empty" );
	switch ( m_InsertMode ) {
	case k_EGeometryInsertMode_Point:
		for ( auto it = m_PointsDict.begin(); it != m_PointsDict.end(); ) {
			if ( it->second.second ) { m_PointsDict.erase( it++ ); }
			else {
				ImGui::Selectable( it->first.ToString(), &it->second.second );
				++it;
			}
		}
		break;
	case k_EGeometryInsertMode_Ray:
		for ( auto it = m_RaysDict.begin(); it != m_RaysDict.end(); ) {
			if ( it->second.second ) { m_RaysDict.erase( it++ ); }
			else {
				ImGui::Selectable( it->first.ToString(), &it->second.second );
				++it;
			}
		}
		break;
	case k_EGeometryInsertMode_AABB:
		for ( auto it = m_AABBsDict.begin(); it != m_AABBsDict.end(); ) {
			if ( it->second.second ) { m_AABBsDict.erase( it++ ); }
			else {
				ImGui::Selectable( it->first.ToString(), &it->second.second );
				++it;
			}
		}
		break;
	case k_EGeometryInsertMode_Circle:
		for ( auto it = m_CirclesDict.begin(); it != m_CirclesDict.end(); ) {
			if ( it->second.second ) { m_CirclesDict.erase( it++ ); }
			else {
				ImGui::Selectable( it->first.ToString(), &it->second.second );
				++it;
			}
		}
		break;
	}
	ImGui::ListBoxFooter();
}

void CGeometryPlayground::OnRender( CRenderer& renderer ) const {
	if ( m_StartPos == Vec2::zero ) {
		for ( auto&& point : m_PointsDict ) {
			renderer.SetDrawColor( point.second.first );
			renderer.DrawPoint( point.first );
		}

		for ( auto&& ray : m_RaysDict ) {
			renderer.SetDrawColor( ray.second.first );
			renderer.DrawRay( ray.first );
		}

		for ( auto&& aabb : m_AABBsDict ) {
			renderer.SetDrawColor( aabb.second.first );
			renderer.DrawAABB( aabb.first );
		}

		for ( auto&& circle : m_CirclesDict ) {
			renderer.SetDrawColor( circle.second.first );
			renderer.DrawCircle( circle.first );
		}
	}
	else {
		switch ( m_InsertMode ) {
		case k_EGeometryInsertMode_Point:
			RenderInsertPoint( renderer );
			break;
		case k_EGeometryInsertMode_Ray:
			RenderInsertRay( renderer );
			break;
		case k_EGeometryInsertMode_AABB:
			RenderInsertAABB( renderer );
			break;
		case k_EGeometryInsertMode_Circle:
			RenderInsertCircle( renderer );
			break;
		}
	}
}

void CGeometryPlayground::RenderInsertPoint( CRenderer& renderer ) const {
	Vec2 point = g_MousePosition;

	for ( auto&& point2 : m_PointsDict ) {
		renderer.SetDrawColor( point2.second.first );
		renderer.DrawPoint( point2.first );

		if ( (m_TestGeometry & k_EGeometryInsertMode_Point) && m_TestMode == k_EGeometryTestMode_Distance ) {
			renderer.DrawLine( point, point2.first );
		}
	}

	for ( auto&& ray : m_RaysDict ) {
		renderer.SetDrawColor( ray.second.first );
		renderer.DrawRay( ray.first );

		if ( (m_TestGeometry & k_EGeometryInsertMode_Ray) && m_TestMode == k_EGeometryTestMode_Distance ) {
			renderer.DrawLine( g_MousePosition, ray.first.GetClosestPoint( g_MousePosition ) );
		}
	}

	for ( auto&& aabb : m_AABBsDict ) {
		if ( (m_TestGeometry & k_EGeometryInsertMode_Point) && m_TestMode == k_EGeometryTestMode_Collision && aabb.first.ContainsPoint( point ) ) {
			renderer.SetDrawColor( Vec4( 1, 0, 0, 1 ) );
		}
		else {
			renderer.SetDrawColor( aabb.second.first );
		}
		renderer.DrawAABB( aabb.first );
	}

	for ( auto&& circle : m_CirclesDict ) {
		if ( (m_TestGeometry & k_EGeometryInsertMode_Point) && m_TestMode == k_EGeometryTestMode_Collision && circle.first.ContainsPoint( point ) ) {
			renderer.SetDrawColor( Vec4( 1, 0, 0, 1 ) );
		}
		else {
			renderer.SetDrawColor( circle.second.first );
		}
		renderer.DrawCircle( circle.first );
	}
}

void CGeometryPlayground::RenderInsertRay( CRenderer& renderer ) const {
	Ray ray = Ray( m_StartPos, (m_StartPos + ((g_MousePosition - m_StartPos).normalized() * 10000)) );

	for ( auto&& point : m_PointsDict ) {
		renderer.SetDrawColor( point.second.first );
		renderer.DrawPoint( point.first );

		if ( (m_TestGeometry & k_EGeometryInsertMode_Point) && m_TestMode == k_EGeometryTestMode_Distance ) {
			renderer.DrawLine( point.first, ray.GetClosestPoint( point.first ) );
		}
	}

	for ( auto&& ray2 : m_RaysDict ) {
		renderer.SetDrawColor( ray2.second.first );
		renderer.DrawRay( ray2.first );
	}

	for ( auto&& aabb : m_AABBsDict ) {
		renderer.SetDrawColor( aabb.second.first );
		renderer.DrawAABB( aabb.first );
	}

	for ( auto&& circle : m_CirclesDict ) {
		renderer.SetDrawColor( circle.second.first );
		renderer.DrawCircle( circle.first );
	}

	renderer.SetDrawColor( m_DrawColor );
	renderer.DrawRay( ray );
	
	/*
	if ( m_bTestAgainstRays ) {
	for ( auto&& ray : m_RaysDict ) {
	renderer.SetDrawColor( ray.second.first );
	renderer.DrawLine( g_MousePosition, GetClosestPointOnRay( ray.first, g_MousePosition ) );
	}
	}*/
}

void CGeometryPlayground::RenderInsertAABB( CRenderer& renderer ) const {
	AABB aabb = AABB::FromMinsMaxs( m_StartPos, g_MousePosition );

	for ( auto&& point : m_PointsDict ) {
		if ( (m_TestGeometry & k_EGeometryInsertMode_Point) && m_TestMode == k_EGeometryTestMode_Collision && aabb.ContainsPoint( point.first ) ) {
			renderer.SetDrawColor( Vec4( 1, 0, 0, 1 ) );
		}
		else {
			renderer.SetDrawColor( point.second.first );
		}
		renderer.DrawPoint( point.first );
	}

	for ( auto&& ray : m_RaysDict ) {
		renderer.SetDrawColor( ray.second.first );
		renderer.DrawRay( ray.first );
	}

	for ( auto&& aabb2 : m_AABBsDict ) {
		if ( (m_TestGeometry & k_EGeometryInsertMode_Point) && m_TestMode == k_EGeometryTestMode_Collision && aabb.Intersects( aabb2.first ) ) {
			renderer.SetDrawColor( Vec4( 1, 0, 0, 1 ) );
		}
		else {
			renderer.SetDrawColor( aabb2.second.first );
		}
		renderer.DrawAABB( aabb2.first );
	}

	for ( auto&& circle : m_CirclesDict ) {
		renderer.SetDrawColor( circle.second.first );
		renderer.DrawCircle( circle.first );
	}

	renderer.SetDrawColor( m_DrawColor );
	renderer.DrawAABB( aabb );
}

void CGeometryPlayground::RenderInsertCircle( CRenderer& renderer ) const {
	Circle circle = Circle( m_StartPos, (m_StartPos - g_MousePosition).magnitude() );

	for ( auto&& point : m_PointsDict ) {
		if ( (m_TestGeometry & k_EGeometryInsertMode_Point) && m_TestMode == k_EGeometryTestMode_Collision && circle.ContainsPoint( point.first ) ) {
			renderer.SetDrawColor( Vec4( 1, 0, 0, 1 ) );
		}
		else {
			renderer.SetDrawColor( point.second.first );
		}
		renderer.DrawPoint( point.first );
	}

	for ( auto&& ray : m_RaysDict ) {
		renderer.SetDrawColor( ray.second.first );
		renderer.DrawRay( ray.first );
	}

	for ( auto&& aabb : m_AABBsDict ) {
		renderer.SetDrawColor( aabb.second.first );
		renderer.DrawAABB( aabb.first );
	}

	for ( auto&& circle2 : m_CirclesDict ) {
		if ( (m_TestGeometry & k_EGeometryInsertMode_Circle) && m_TestMode == k_EGeometryTestMode_Collision && circle.Intersects( circle2.first ) ) {
			renderer.SetDrawColor( Vec4( 1, 0, 0, 1 ) );
		}
		else {
			renderer.SetDrawColor( circle2.second.first );
		}
		renderer.DrawCircle( circle2.first );
	}

	renderer.SetDrawColor( m_DrawColor );
	renderer.DrawCircle( circle );
}

void CGeometryPlayground::ClearGeometry() {
	m_PointsDict.clear();
	m_RaysDict.clear();
	m_AABBsDict.clear();
	m_CirclesDict.clear();
	m_StartPos = Vec2::zero;
}
