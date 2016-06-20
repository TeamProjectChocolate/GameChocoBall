#include "stdafx.h"
#include "FireJet.h"
#include "CourceDef.h"


CFireJet::CFireJet()
{
}


CFireJet::~CFireJet()
{
}

void CFireJet::Initialize(){
	m_IntervalTime = 6.0f;
	m_JetTime = 6.0f;
	m_ParticleType = PARTICLE_TYPE::FIREGIMMICK;
	strcpy(m_pFileName, "FireGimmickTEST");
	m_pPlayer = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
	m_vibration.Initialize();
	D3DXVec3Normalize(&(m_vibration.m_dir), &(m_TargetCource.endPosition - m_TargetCource.startPosition));
	m_vibration.m_ReflectionTime = 0.01f;
	m_vibration.m_VibrationTime = 3.0f;
	m_vibration.m_VibrationAmount = D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	CJetGimmick::Initialize();
}

void CFireJet::Update(){

	//m_TargetCource = m_pPlayer->GetCourceDef()->FindCource(m_pPlayer->GetPos());
	////m_vibration.Activate();
	//m_vibration.m_VibrationTime = 0.0f;
	//m_vibration.SetIsVibration(true);
	//D3DXVec3Normalize(&(m_vibration.m_dir), &(m_TargetCource.endPosition - m_TargetCource.startPosition));
	//m_vibration.SetTarget(m_pPlayer->GetPosRef());
	//m_vibration.Update();
	CJetGimmick::Update();
}
