#pragma once
#include "pch.h"
#include "CBaseScene.h"

class CHTree : public CBaseScene {
public:
	virtual const char * GetName() const override;
	virtual void OnInit() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnUpdate( const float dt, CInputManager& input ) override;
	virtual void OnInterface() override;
	virtual void OnRender( CRenderer& renderer ) const override;

private:
	int m_Iterations = 2;
};
