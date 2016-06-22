#pragma once
#include "GameObject.h"
#include "ParticleEmitter.h"
#include "Audio.h"
#include "Camera.h"

class CJetGimmick :
	public CGameObject
{
public:
	CJetGimmick();
	~CJetGimmick();
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Draw()override;
	void SoundPlay();
	void SetAudio(CAudio* audio){
		m_pAudio = audio;
	}
	void SetCamera(CCamera* pCamera){
		m_pCamera = pCamera;
	}
	void SetDirection(D3DXVECTOR3 dir){
		m_pEmitter->SetDirection(dir);
	}
	void SetPos(D3DXVECTOR3 pos)override{
		m_pEmitter->SetEmitPos(pos);
	}
	D3DXVECTOR3 GetPos()override{
		return m_pEmitter->GetEmitPos();
	}
	void SetEmitterName(LPCSTR name){
		strcpy(m_pFileName, name);
	}
private:
	CParticleEmitter* m_pEmitter;
	CAudio* m_pAudio;
	CCamera* m_pCamera;
	float m_TimeCounter;
	bool m_JetFlg;
protected:
	float m_IntervalTime;
	float m_JetTime;
	PARTICLE_TYPE m_ParticleType;
	char m_SoundName[FILENAME_MAX];
	bool m_IsPlay;
};

