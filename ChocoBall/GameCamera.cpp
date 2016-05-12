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
	m_camera.Update();
}

void CGameCamera::Draw(){
	m_camera.SetPos(SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"))->GetPos() + D3DXVECTOR3(0.0f,1.0f,-7.0f));
	D3DXVECTOR3 Target = (SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"))->GetPos());
	Target.y += 1.0f;
	m_camera.SetTarget(Target);

	SINSTANCE(CRenderContext)->SetCurrentCamera(&m_camera);
}
