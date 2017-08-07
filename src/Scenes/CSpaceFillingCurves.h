#pragma once
#include "pch.h"
#include "CBaseScene.h"

#include <array>
#include <vector>

class CSpaceFillingCurves : public CBaseScene {
public:
	virtual const char * GetName() const override;
	virtual void OnInit() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnUpdate( const float dt, CInputManager& input ) override;
	virtual void OnInterface() override;
	virtual void OnRender( CRenderer& renderer ) const override;

private:
	static std::vector<Vec2> GenerateHilbertCurve( const uint iterations, const uint stepsize );
	static std::vector<Vec2> GenerateZOrderCurve( const uint iterations, const uint stepsize );
	static std::vector<Vec2> GeneratePeanoCurve( const uint iterations, const uint stepsize );

	struct Curve {
		const char* name;
		std::vector<Vec2>(*pfn)(const uint iterations, const uint stepsize);
	};

	uint m_CurrentCurve = 0;
	std::array<Curve, 3> m_Curves = { {
		{ "Hilbert Curve", &CSpaceFillingCurves::GenerateHilbertCurve },
		{ "Z-Order Curve (Morton order)", &CSpaceFillingCurves::GenerateZOrderCurve },
		{ "Peano Curve", &CSpaceFillingCurves::GeneratePeanoCurve },
	} };

	std::vector<Vec2> m_Points;
	
	bool m_bSettingsChanged = true;
	uint m_Iterations = 2;
	uint m_nStepSize = 1;
	bool m_bLoopDrawing = false;
	float m_LoopPercent = 0.0f;
	float m_LoopSpeed = 0.1f;
};
