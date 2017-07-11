#pragma once
#include "main.h"

#include <unordered_map>

class CGeometryPlayground : public CBaseScene {
public:
	virtual const char *GetName() const override;
	virtual void OnInit() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnUpdate() override;
	virtual void OnInterface() override;
	virtual void OnRender( CRenderer& renderer ) const override;

private:
	void RenderInsertPoint( CRenderer& renderer ) const;
	void RenderInsertRay( CRenderer& renderer ) const;
	void RenderInsertAABB( CRenderer& renderer ) const;
	void RenderInsertCircle( CRenderer& renderer ) const;
	void ClearGeometry();

	enum EGeometryInsertMode : unsigned int {
		k_EGeometryInsertMode_None = 0,
		k_EGeometryInsertMode_Point = 1,
		k_EGeometryInsertMode_Ray = 2,
		k_EGeometryInsertMode_AABB = 4,
		k_EGeometryInsertMode_Circle = 8,
	};

	enum EGeometryTestMode : unsigned int {
		k_EGeometryTestMode_Collision,
		k_EGeometryTestMode_Distance,
	};

	Vec4 m_DrawColor = Vec4( 1.0f, 1.0f, 1.0f, 1.0f );

	std::unordered_map<Vec2, std::pair<Vec4, bool>> m_PointsDict;
	std::unordered_map<Ray, std::pair<Vec4, bool>> m_RaysDict;
	std::unordered_map<AABB, std::pair<Vec4, bool>> m_AABBsDict;
	std::unordered_map<Circle, std::pair<Vec4, bool>> m_CirclesDict;

	EGeometryInsertMode m_InsertMode = k_EGeometryInsertMode_Point;
	EGeometryInsertMode m_TestGeometry = (EGeometryInsertMode)0xFFFFFFFF;
	EGeometryTestMode m_TestMode = k_EGeometryTestMode_Collision;
	Vec2 m_StartPos;
};
