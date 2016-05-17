#include "stdafx.h"
#include "CourceCamera.h"
#include "ObjectManager.h"
#include "Player.h"


void CCourceCamera::Initialize(){
	m_courceDef.Initialize();
	CGameCamera::Initialize();
}

void CCourceCamera::Update(){

	CPlayer* pl = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
	D3DXVECTOR3 Target = pl->GetPos();

	COURCE_BLOCK cource = m_courceDef.FindCource(Target);
	D3DXVECTOR3 courceVec = cource.endPosition - cource.startPosition;
	D3DXVECTOR3 Dir;
	D3DXVec3Normalize(&Dir, &courceVec);
	D3DXVECTOR3 pos = pl->GetPos() -  cource.startPosition;
	float t = D3DXVec3Dot(&Dir, &pos);
	pos = cource.startPosition + (Dir*(t-8.0f));
	pos.y = 2.0f;
	//D3DXVECTOR3 Distance = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"))->GetPos();
	D3DXMATRIX Rota;
	//courceVec.x *= Distance.x;
	//courceVec.y *= Distance.y;
	//courceVec.z *= Distance.z;
	//float Dir = D3DXVec3Dot(&courceVec, &Distance);
	D3DXQUATERNION quat;
	//static float f = 0.0f;
	//f++;
	
	//m_camera.SetAxis(SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"))->GetPos());
	m_camera.SetPos(pos);
	Target.y += 0.1f;
	m_camera.SetTarget(Target);
	//m_camera.SetTarget(target);
	CGameCamera::Update();
}

void CCourceCamera::Draw(){
	CGameCamera::Draw();
}