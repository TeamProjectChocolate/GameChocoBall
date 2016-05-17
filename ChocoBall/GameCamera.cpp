#include "stdafx.h"
#include "GameCamera.h"
#include "RenderContext.h"
#include "ObjectManager.h"
#include "Player.h"


CGameCamera::CGameCamera()
{
}


CGameCamera::~CGameCamera()
{
}

void CGameCamera::Initialize(){
	m_camera.Initialize();
	m_camera.SetAspect(static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT);
	SetAlive(true);
}

void CGameCamera::Update(){
#if 0
	CPlayer* pl = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
	m_camera.SetTarget(pl->GetPos() + D3DXVECTOR3(0.0f,1.0f,0.0f));
	m_camera.SetPos(pl->GetPos() + D3DXVECTOR3(0.0f,0.0f,-7.0f));
#else
#endif
	m_camera.Update();
}

void CGameCamera::Draw(){
	SINSTANCE(CRenderContext)->SetCurrentCamera(&m_camera);
}
