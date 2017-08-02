#pragma once

class CRenderer;
class CInputManager;

class CBaseScene {
public:
	virtual const char * GetName() const = 0;
	virtual void OnInit() = 0;
	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;
	virtual void OnUpdate( CInputManager& input ) = 0;
	virtual void OnInterface() = 0;
	virtual void OnRender( CRenderer& renderer ) const = 0;
};
