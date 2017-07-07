#pragma once
#include "main.h"

#include <unordered_map>

class CGeometryPlayground : public CBaseScene {
public:
	virtual const char * GetName() const override;
	virtual void OnInit() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnUpdate() override;
	virtual void OnInterface() override;
	virtual void OnRender( CRenderer& renderer ) const override;

private:
	void ClearGeometry();

	enum EGeometryInsertMode : int {
		k_EGeometryInsertMode_Point,
		k_EGeometryInsertMode_Ray,
		k_EGeometryInsertMode_Plane,
		k_EGeometryInsertMode_Rect,
		k_EGeometryInsertMode_Circle,
	};

	Vec4 m_DrawColor = Vec4( 1.0f, 1.0f, 1.0f, 1.0f );
	std::unordered_map<Vec2, std::pair<Vec4, bool>> m_PointsDict;
	std::unordered_map<Ray, std::pair<Vec4, bool>> m_RaysDict;
	EGeometryInsertMode m_InsertMode = k_EGeometryInsertMode_Point;
	bool m_bInserting = false;
	Vec2 m_StartPos;

	bool m_bTestAgainstPoints = true;
	bool m_bTestAgainstRays = true;
};
