#pragma once
#include "GameObject.h"
#include "Camera.h"


class CGameCamera :
	public CGameObject
{
public:
	CGameCamera();
	~CGameCamera();
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Draw()override;
private:
	CCamera m_camera;
};

