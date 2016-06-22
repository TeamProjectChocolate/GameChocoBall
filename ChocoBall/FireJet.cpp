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
	CJetGimmick::Initialize();
}

void CFireJet::Update(){
	CJetGimmick::Update();
}

bool CFireJet::IsCollision(D3DXVECTOR3 pos, float radius){
	return false;
}