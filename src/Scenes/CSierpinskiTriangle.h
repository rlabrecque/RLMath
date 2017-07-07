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
};
