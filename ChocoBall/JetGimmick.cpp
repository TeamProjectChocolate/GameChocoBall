#include "stdafx.h"
#include "JetGimmick.h"


CJetGimmick::CJetGimmick()
{

}


CJetGimmick::~CJetGimmick()
{

}


void CJetGimmick::Initialize(){
	SetAlive(true);
	CCourceCamera* camera = SINSTANCE(CObjectManager)->FindGameObject<CCourceCamera>(_T("Camera"));
	m_pCamera = camera->GetCamera();
	m_pEmitter = CParticleEmitter::EmitterCreate(m_pFileName, m_ParticleType, m_transform.position, m_pCamera, false);
	m_IntervalCounter = 0.0f;
	m_JetCounter = 0.0f;
	m_IsPlay = true;
}

void CJetGimmick::Update(){
	if (m_JetFlg){
		if (m_JetCounter <= m_JetTime){
			m_pEmitter->SetEmitFlg(true);
			SoundPlay();
		}
		else{
			m_JetCounter = 0.0f;
			//m_pAudio->StopCue(m_SoundName);
			m_JetFlg = false;
			m_IsPlay = true;
			return;
		}
		m_JetCounter += 1.0f / 60.0f;
	}
	else{
		if (m_IntervalCounter >= m_IntervalTime){
			m_JetFlg = true;
			m_IntervalCounter = 0.0f;
			return;
		}
		else{
			m_pEmitter->SetEmitFlg(false);
		}
		m_IntervalCounter += 1.0f / 60.0f;
	}
}

void CJetGimmick::Draw(){
}

void CJetGimmick::SoundPlay(){
	if (m_IsPlay){
		//m_pAudio->PlayCue(m_SoundName, true);
		m_IsPlay = false;
	}
}