#include "CGeometryPlayground.h"

#include "CRenderer.h"
#define IMGUI_DISABLE_TEST_WINDOWS
#include "imgui.h"
#undef IMGUI_DISABLE_TEST_WINDOWS

const char * CGeometryPlayground::GetName() const {
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
	{
		static EGeometryInsertMode lastGeometryInsertMode;

		if ( m_InsertMode != lastGeometryInsertMode ) {
			m_StartPos = Vec2::zero;
			m_bInserting = false;
			lastGeometryInsertMode = m_InsertMode;
		}
	}

	if ( g_MousePosition.x > (WindowWidth - 320) ) {
		return;
	}

	if ( g_MouseButtonDownThisFrame[0] ) {
		switch ( m_InsertMode ) {
		case k_EGeometryInsertMode_Point:
			break;
		case k_EGeometryInsertMode_Ray:
			break;
		}

		m_StartPos = g_MousePosition;
		m_bInserting = true;
	}

	if ( g_MouseButtonUpThisFrame[0] ) {
		switch ( m_InsertMode ) {
		case k_EGeometryInsertMode_Point:
			m_PointsDict[g_MousePosition] = { m_DrawColor, false };
			break;
		case k_EGeometryInsertMode_Ray:
			m_RaysDict[Ray( m_StartPos, (m_StartPos + ((g_MousePosition - m_StartPos).normalized() * 10000)) )] = { m_DrawColor, false };
			break;
		}

		m_bInserting = false;
	}
}

void CGeometryPlayground::OnInterface() {
	ImGui::ColorEdit3( "Draw Color", m_DrawColor.data );

	if ( ImGui::Button( "Clear Geometry" ) ) {
		ClearGeometry();
	}

	ImGui::RadioButton( "Point", (int*)&m_InsertMode, k_EGeometryInsertMode_Point ); ImGui::SameLine();
	ImGui::RadioButton( "Ray", (int*)&m_InsertMode, k_EGeometryInsertMode_Ray ); ImGui::SameLine();
	ImGui::RadioButton( "Plane", (int*)&m_InsertMode, k_EGeometryInsertMode_Plane ); ImGui::SameLine();
	ImGui::RadioButton( "Rect", (int*)&m_InsertMode, k_EGeometryInsertMode_Rect ); ImGui::SameLine();
	ImGui::RadioButton( "Circle", (int*)&m_InsertMode, k_EGeometryInsertMode_Circle );

	ImGui::Separator();

	ImGui::Checkbox( "Test Against Points", &m_bTestAgainstPoints );
	ImGui::Checkbox( "Test Against Rays", &m_bTestAgainstRays );

	ImGui::Separator();

	if ( m_bInserting ) {
		ImGui::Text( "StartPos: %s", m_StartPos.ToString() );
	}
	else {
		ImGui::Text( "StartPos: " );
	}

	ImGui::PushItemWidth( -1 );
	ImGui::ListBoxHeader( "##empty" );
	switch ( m_InsertMode ) {
	case k_EGeometryInsertMode_Point:
		for ( auto&& point : m_PointsDict ) {
			ImGui::Selectable( point.first.ToString(), &point.second.second );
		}
		break;
	case k_EGeometryInsertMode_Ray:
		for ( auto&& ray : m_RaysDict ) {
			ImGui::Selectable( ray.first.ToString(), &ray.second.second );
		}
		break;
	}
	ImGui::ListBoxFooter();
}

void CGeometryPlayground::OnRender( CRenderer& renderer ) const {
	for ( auto&& point : m_PointsDict ) {
		renderer.SetDrawColor( point.second.first );
		renderer.DrawPoint( point.first );
	}

	for ( auto&& ray : m_RaysDict ) {
		renderer.SetDrawColor( ray.second.first );
		renderer.DrawRay( ray.first );
	}

	if ( m_bInserting ) {
		switch ( m_InsertMode ) {
		case k_EGeometryInsertMode_Point:
			if ( m_bTestAgainstPoints ) {
				for ( auto&& point : m_PointsDict ) {
					renderer.SetDrawColor( point.second.first );
					renderer.DrawLine( g_MousePosition, point.first );
				}
			}

			if ( m_bTestAgainstRays ) {
				for ( auto&& ray : m_RaysDict ) {
					renderer.SetDrawColor( ray.second.first );
					renderer.DrawLine( g_MousePosition, GetClosestPointOnRay(ray.first, g_MousePosition) );
				}
			}

			break;
		case k_EGeometryInsertMode_Ray:
			Ray ray = Ray( m_StartPos, (m_StartPos + ((g_MousePosition - m_StartPos).normalized() * 10000)) );

			renderer.SetDrawColor( m_DrawColor );
			renderer.DrawRay( ray );

			if ( m_bTestAgainstPoints ) {
				for ( auto&& point : m_PointsDict ) {
					renderer.SetDrawColor( point.second.first );
					renderer.DrawLine( point.first, GetClosestPointOnRay( ray, point.first ) );
				}
			}

			/*
			if ( m_bTestAgainstRays ) {
				for ( auto&& ray : m_RaysDict ) {
					renderer.SetDrawColor( ray.second.first );
					renderer.DrawLine( g_MousePosition, GetClosestPointOnRay( ray.first, g_MousePosition ) );
				}
			}*/

			break;
		}
	}
}

void CGeometryPlayground::ClearGeometry() {
	m_PointsDict.clear();
	m_RaysDict.clear();
	m_StartPos = Vec2::zero;
}
