#pragma once
#include "pch.h"
#include "CBaseScene.h"

#include <vector>

class CHomingMissile : public CBaseScene {
public:
	virtual const char * GetName() const override;
	virtual void OnInit() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnUpdate( const float dt, CInputManager& input ) override;
	virtual void OnInterface() override;
	virtual void OnRender( CRenderer& renderer ) const override;

private:
	void ClearMissiles();

	struct Missile {
		Vec2 pos;
		Vec2 dir;
		float radius;
	};

	std::vector<Missile> m_Missiles;
	float m_MissileSpeed = 50.0f;
};
