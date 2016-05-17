#pragma once
#include "GameCamera.h"
#include "CourceDef.h"

class CCourceCamera :
	public CGameCamera
{
public:
	CCourceCamera(){};
	~CCourceCamera(){};
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	CCourceDef m_courceDef;
};

