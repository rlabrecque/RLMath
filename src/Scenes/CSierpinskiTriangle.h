#pragma once
#include "pch.h"
#include "CBaseScene.h"

class CSierpinskiTriangle : public CBaseScene {
public:
	virtual const char * GetName() const override;
	virtual void OnInit() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnUpdate( CInputManager& input ) override;
	virtual void OnInterface() override;
	virtual void OnRender( CRenderer& renderer ) const override;

private:
	void DrawSierpinskiTriangleRecursive( CRenderer& renderer, Vec2 A, Vec2 B, Vec2 C, int i ) const;

	int m_Iterations;

	Vec2 m_point1;
	Vec2 m_point2;
	Vec2 m_point3;

	Vec2 m_Translate;
	Vec3 m_Rot;
	Vec2 m_Scale;

	bool m_bAutomaticallyRotate;
	bool m_bAutomaticallyScale;
};
