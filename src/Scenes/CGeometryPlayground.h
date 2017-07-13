#pragma once
#include "main.h"

#include <vector>

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
	void RenderInsertPoint( CRenderer& renderer, const Vec2 point ) const;
	void RenderInsertRay( CRenderer& renderer, const Ray ray ) const;
	void RenderInsertAABB( CRenderer& renderer, const AABB aabb ) const;
	void RenderInsertCircle( CRenderer& renderer, const Circle circle ) const;
	void ClearGeometry();

	enum EGeometry : unsigned int {
		k_EGeometry_None = 0,
		k_EGeometry_Point = 1,
		k_EGeometry_Ray = 2,
		k_EGeometry_AABB = 4,
		k_EGeometry_Circle = 8,
	};

	enum EGeometryTestMode : unsigned int {
		k_EGeometryTestMode_Collision,
		k_EGeometryTestMode_Distance,
	};

	struct GeometryEntity {
		EGeometry type;
		Vec4 color;

		union {
			Vec2 point;
			Ray ray;
			AABB aabb;
			Circle circle;
		};

		inline GeometryEntity() {}
	};

	Vec4 m_DrawColor = Vec4( 1.0f, 1.0f, 1.0f, 1.0f );

	std::vector<GeometryEntity> m_GeometryEntities;

	EGeometry m_InsertMode = k_EGeometry_Point;
	EGeometry m_TestGeometry = (EGeometry)~k_EGeometry_None;
	EGeometryTestMode m_TestMode = k_EGeometryTestMode_Collision;
	Vec2 m_StartPos;
};
