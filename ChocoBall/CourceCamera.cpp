#include "stdafx.h"
#include "CourceCamera.h"
#include "ObjectManager.h"
#include "Player.h"


namespace{
	void VectorSmoothDamp(
		D3DXVECTOR3& vOut, 
		const D3DXVECTOR3& currentPos, 
		const D3DXVECTOR3& targetPos,
		D3DXVECTOR3& linearVelocity,
		int smoothTime
	)
	{
		D3DXVECTOR3 dist = targetPos - currentPos;
		D3DXVECTOR3 vel = dist /= smoothTime;
		linearVelocity = vel;
		vOut = currentPos + linearVelocity;
	}
}
void CCourceCamera::Initialize(){
	m_courceDef.SetStageID(m_StageID);
	m_courceDef.Initialize();
	D3DXVECTOR3 Target = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"))->GetPos();
	COURCE_BLOCK StartBlock = m_courceDef.FindCource(Target);
	CGameCamera::Initialize();
	Target.y += 0.1f;
	m_camera.SetTarget(Target);
	m_CompCamera = false;
	m_isFirst = true;
	m_cameraPosSpeed.x = 0.0f;
	m_cameraPosSpeed.y = 0.0f;
	m_cameraPosSpeed.z = 0.0f;
}

void CCourceCamera::Update(){

	CPlayer* pl = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
	D3DXVECTOR3 Target = pl->GetPos();

	m_NowCource = m_courceDef.FindCource(Target);
	Target.y += 0.1f;
	m_camera.SetTarget(Target);
	D3DXVECTOR3 courceVec = m_NowCource.endPosition - m_NowCource.startPosition;
	D3DXVECTOR3 Dir;
	D3DXVec3Normalize(&Dir, &courceVec);
	D3DXVECTOR3 TargetPos = pl->GetPos() -  m_NowCource.startPosition;
	float t = D3DXVec3Dot(&Dir, &TargetPos);
	TargetPos = m_NowCource.startPosition + (Dir*(t-8.0f));
	TargetPos.y += 2.5f;

	if (!m_isFirst){
		VectorSmoothDamp(
			m_NowPos,
			m_NowPos,
			TargetPos,
			m_cameraPosSpeed,
			10);
	}
	else{
		m_NowPos = m_NowCource.startPosition/*TargetPos*/;
		m_NowPos.y += 2.5f;
		m_isFirst = false;
	}
	m_camera.SetPos(m_NowPos);
	//m_camera.SetTarget(target);
	CGameCamera::Update();
}

void CCourceCamera::Draw(){
	CGameCamera::Draw();
}