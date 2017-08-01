#pragma once
#include "main.h"

class CSierpinskiTriangle : public CBaseScene {
public:
	virtual const char * GetName() const override;
	virtual void OnInit() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnUpdate() override;
	virtual void OnInterface() override;
	virtual void OnRender(CRenderer& renderer) const override;

private:
	void DrawSierpinskiTriangleRecursive( CRenderer& renderer, Vec2 A, Vec2 B, Vec2 C, int i ) const;

	Vec2 m_point1;
	Vec2 m_point2;
	Vec2 m_point3;

	Vec2 m_Transform;
	Vec2 m_Scale;
	float m_Rot;

	bool m_bAutomaticallyScale;
};
