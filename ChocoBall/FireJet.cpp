#include "stdafx.h"
#include "FireJet.h"


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
	CJetGimmick::Initialize();
}

void CFireJet::Update(){
	CJetGimmick::Update();
}
