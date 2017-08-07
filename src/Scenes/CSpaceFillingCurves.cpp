#include "pch.h"
#include "CInputManager.h"
#include "CRenderer.h"
#include "CSpaceFillingCurves.h"
#include "Color.h"
#include "imgui.h"

#if _MSC_VER
#include <intrin.h>
#endif

const char * CSpaceFillingCurves::GetName() const {
	return "Space-filling Curves";
}

void CSpaceFillingCurves::OnInit() {
}

void CSpaceFillingCurves::OnEnable() {

}

void CSpaceFillingCurves::OnDisable() {
}

void CSpaceFillingCurves::OnUpdate( const float dt, CInputManager& input ) {
	if ( m_bSettingsChanged ) {
		m_Points = m_Curves[m_CurrentCurve].pfn( m_Iterations, m_nStepSize );

		m_bSettingsChanged = false;
	}

	if ( m_bLoopDrawing ) {
		m_LoopPercent += dt * m_LoopSpeed;

		if ( m_LoopPercent >= 1.0f ) {
			m_LoopPercent = 0.0f;
		}
	}
}

void CSpaceFillingCurves::OnInterface() {
	ImGui::Text( m_Curves[m_CurrentCurve].name );
	ImGui::SameLine();
	if ( ImGui::Button( "Select.." ) ) {
		ImGui::OpenPopup( "select" );
	}

	if ( ImGui::BeginPopup( "select" ) ) {
		for ( int i = 0; i < (int)m_Curves.size(); ++i ) {
			if ( ImGui::Selectable( m_Curves[i].name ) ) {
				m_CurrentCurve = i;
				m_bSettingsChanged = true;
			}
		}
		ImGui::EndPopup();
	}

	ImGui::Separator();

	m_bSettingsChanged |= ImGui::SliderInt( "Iterations", reinterpret_cast<int*>(&m_Iterations), 2, 32 );
	m_bSettingsChanged |= ImGui::SliderInt( "Step Size", reinterpret_cast<int*>(&m_nStepSize), 1, 32 );
	ImGui::Checkbox( "Loop Drawing", &m_bLoopDrawing );
	ImGui::SliderFloat( "Loop Speed", &m_LoopSpeed, 0.0f, 1.0f );
	ImGui::SliderFloat( "Loop Percent", &m_LoopPercent, 0.0f, 1.0f);
}

void CSpaceFillingCurves::OnRender( CRenderer& renderer ) const {
	Vec4 prevColor;
	Vec4 currColor;
	Vec2 prev;

	const uint nPoints = m_Points.size();
	for ( uint i = 0; i < nPoints; ++i ) {
		const float percentComplete = static_cast<float>(i) / static_cast<float>(nPoints);

		const Vec2 currDrawPos = Vec2( 20 + m_Points[i].x * 20, 20 + m_Points[i].y * 20 );
		const Vec2 prevDrawPos = Vec2( 20 + prev.x * 20, 20 + prev.y * 20 );

		const Vec4 color = Color::HSL2RGB( percentComplete, 0.8f, 0.5f );

		if ( i != 0 ) {
			renderer.DrawLine( prevDrawPos, currDrawPos, prevColor, color );
		}
		
		if ( m_bLoopDrawing && percentComplete >= m_LoopPercent ) {
			break;
		}

		prev = m_Points[i];
		prevColor = color;
	}
	
	// Temporary hack because we don't have z axis drawing yet, so the dots were getting overwritten sometimes.
	for ( uint i = 0; i < nPoints; ++i ) {
		const float percentComplete = static_cast<float>(i) / static_cast<float>(nPoints);

		const Vec2 currDrawPos = Vec2( 20 + m_Points[i].x * 20, 20 + m_Points[i].y * 20 );
		const Vec2 prevDrawPos = Vec2( 20 + prev.x * 20, 20 + prev.y * 20 );

		renderer.SetDrawColor( 1, 1, 1 );
		renderer.DrawPoint( currDrawPos );

		if ( m_bLoopDrawing && percentComplete >= m_LoopPercent ) {
			break;
		}

		prev = m_Points[i];
	}
}

std::vector<Vec2> CSpaceFillingCurves::GenerateHilbertCurve( const uint iterations, const uint stepsize ) {
	const uint N = iterations * iterations;
	
	std::vector<Vec2> ret;
	ret.reserve( N );

	for ( uint i = 0; i < N; i += stepsize ) {
		uint x = 0;
		uint y = 0;

		for ( uint j = 1, t = i; j < iterations; j *= 2 ) {
			uint rx = 1 & (t / 2);
			uint ry = 1 & (t ^ rx);

			// Rotate
			if ( ry == 0 ) {
				if ( rx == 1 ) {
					x = j - 1 - x;
					y = j - 1 - y;
				}

				//Swap x and y
				uint temp = x;
				x = y;
				y = temp;
			}

			x += j * rx;
			y += j * ry;
			t /= 4;
		}

		ret.emplace_back( Vec2( static_cast<float>(x), static_cast<float>(y) ) );
	}

	return ret;
}

std::vector<Vec2> CSpaceFillingCurves::GenerateZOrderCurve( const uint iterations, const uint stepsize ) {
	const uint N = iterations * iterations;

	std::vector<Vec2> ret;
	ret.reserve( N );

	constexpr auto& GetSecondBits = []( const uint m ) {
		const uint mask[] = { 0xFFFFFFFF, 0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F, 0x33333333, 0x55555555 };
		uint x = m & mask[5];
		x = (x ^ (x >> 1)) & mask[4];
		x = (x ^ (x >> 2)) & mask[3];
		x = (x ^ (x >> 4)) & mask[2];
		x = (x ^ (x >> 8)) & mask[1];
		x = (x ^ (x >> 16)) & mask[0];
		return x;
	};

	for ( uint i = 0; i < N; i += stepsize ) {
		ret.emplace_back( Vec2( static_cast<float>(GetSecondBits( i )), static_cast<float>(GetSecondBits( i >> 1 )) ) );
	}
	
	return ret;
}

static void Peano( std::vector<Vec2>& v, Vec2& pos, const uint i, const uint n, const uint e, const uint s, const uint w ) {
	static const int DX[] = { 0, 1, 0, -1 };
	static const int DY[] = { 1, 0, -1, 0 };
	
	if ( i > 0 ) {
		Peano( v, pos, i - 1, n, e, s, w );
		pos.y += DY[n];
		v.emplace_back( pos );

		Peano( v, pos, i - 1, n, w, s, e );
		pos.y += DY[n];
		v.emplace_back( pos );

		Peano( v, pos, i - 1, n, e, s, w );
		pos.x += DX[e];
		v.emplace_back( pos );

		Peano( v, pos, i - 1, s, e, n, w );
		pos.y += DY[s];
		v.emplace_back( pos );

		Peano( v, pos, i - 1, s, w, n, e );
		pos.y += DY[s];
		v.emplace_back( pos );

		Peano( v, pos, i - 1, s, e, n, w );
		pos.x += DX[e];
		v.emplace_back( pos );

		Peano( v, pos, i - 1, n, e, s, w );
		pos.y += DY[n];
		v.emplace_back( pos );

		Peano( v, pos, i - 1, n, w, s, e );
		pos.y += DY[n];
		v.emplace_back( pos );

		Peano( v, pos, i - 1, n, e, s, w );
	}
}

std::vector<Vec2> CSpaceFillingCurves::GeneratePeanoCurve( const uint iterations, const uint stepsize ) {
	std::vector<Vec2> v;
	v.reserve( (uint)RL_Pow( 4, (float)iterations-1 ) );
	
	Vec2 pos;
	v.emplace_back( pos );

	Peano( v, pos, iterations-1, 0, 1, 2, 3 );

	return v;
}
