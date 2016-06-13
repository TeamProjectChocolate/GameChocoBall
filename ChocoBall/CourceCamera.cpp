#include "stdafx.h"
#include "CourceCamera.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Infomation.h"


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
	//D3DXVECTOR3 Target = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"))->GetPos();
	//COURCE_BLOCK StartBlock = m_courceDef.FindCource(Target);
	CGameCamera::Initialize();
	//Target.y += 0.1f;
	//m_camera.SetTarget(Target);
	m_CompCamera = false;
	m_isFirst = true;
	m_cameraPosSpeed.x = 0.0f;
	m_cameraPosSpeed.y = 0.0f;
	m_cameraPosSpeed.z = 0.0f;
	m_IsEnd = false;
}

void CCourceCamera::Update(){

	if (m_GameState == GAMEEND_ID::CONTINUE){
		CPlayer* pl = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
		D3DXVECTOR3 Target = pl->GetPos();

		m_NowCource = m_courceDef.FindCource(Target);
		Target.y += 0.1f;
		m_camera.SetTarget(Target);
		D3DXVECTOR3 courceVec = m_NowCource.endPosition - m_NowCource.startPosition;
		D3DXVECTOR3 Dir;
		D3DXVec3Normalize(&Dir, &courceVec);
		D3DXVECTOR3 TargetPos = pl->GetPos() - m_NowCource.startPosition;
		float t = D3DXVec3Dot(&Dir, &TargetPos);
		TargetPos = m_NowCource.startPosition + (Dir*(t - 8.0f));
		TargetPos.y += 2.5f;
		//TargetPos.y = 2.0f;

		if (!m_isFirst){
			VectorSmoothDamp(
				m_NowPos,
				m_NowPos,
				TargetPos,
				m_cameraPosSpeed,
				10);
		}
		else{
			m_NowPos = TargetPos;
			m_isFirst = false;
		}
		m_camera.SetPos(m_NowPos);

		//m_camera.SetTarget(target);
	}
	else if (m_GameState == GAMEEND_ID::CLEAR){
		ClearCamera();
	}
	CGameCamera::Update();
}

void CCourceCamera::Draw(){
	CGameCamera::Draw();
}

void CCourceCamera::ClearCamera(){
	D3DXVECTOR3 courceVec = m_NowCource.startPosition - m_NowPos;

	float length = D3DXVec3Length(&courceVec);
	if (1.0f <= length){
		D3DXVECTOR3 Dir;
		D3DXVec3Normalize(&Dir, &courceVec);
		D3DXVECTOR3 TargetPos = m_NowCource.startPosition;
		TargetPos.y += 2.5f;
		VectorSmoothDamp(
			m_NowPos,
			m_NowPos,
			TargetPos,
			m_cameraPosSpeed,
			30);
		m_camera.SetPos(m_NowPos);
	}
	else{
		m_IsEnd = true;
	}
	if (m_IsEnd){
		return;
	}
	m_IsEnd = false;
}