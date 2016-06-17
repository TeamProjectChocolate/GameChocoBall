#pragma once
#include "GameObject.h"
#include "CourceCamera.h"
#include "Particle.h"
#include "ParticleParameterTable.h"
#include "ObjectManager.h"

#define MAX_NAME 256

// パーティクルの発生機
class CParticleEmitter:public CGameObject
{
public:
	static CParticleEmitter* EmitterCreate(LPCSTR EmitterName, PARTICLE_TYPE type,D3DXVECTOR3 pos,CCamera* pcamera,bool flg){
		CParticleEmitter* pEmitter = SINSTANCE(CObjectManager)->GenerationObject<CParticleEmitter>(_T(EmitterName), PRIORTY::EMITTER, false);
		pEmitter->SetCamera(pcamera);
		pEmitter->SetEmitParameter(reinterpret_cast<SParticleEmitParameter*>(ParticleParamPT_Array[type]));
		pEmitter->SetEmitPos(pos);
		pEmitter->SetEmitterName(EmitterName);
		pEmitter->SetEmitFlg(flg);
		pEmitter->Initialize();
		return pEmitter;
	}

	CParticleEmitter();
	~CParticleEmitter();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void ApplyForce(const D3DXVECTOR3&);
	void SetCamera(CCamera* camera){
		m_camera = camera;
	}
	void SetEmitParameter(SParticleEmitParameter* param){
		m_param = param;
	}
	void SetEmitPos(D3DXVECTOR3 pos){
		m_emitPosition = pos;
	}
	D3DXVECTOR3 GetEmitPos(){
		return m_emitPosition;
	}
	void SetEmitterName(LPCSTR name){
		CH_ASSERT(strlen(name) < MAX_NAME);
		strcpy(m_EmitterName, name);
	}
	void SetEmitFlg(bool flg){
		m_EmitFlg = flg;
	}
	void SetDirection(D3DXVECTOR3 dir){
		m_dir = dir;
	}
private:
	float m_timer;
	CRandom m_random;
	CCamera* m_camera;
	SParticleEmitParameter* m_param;
	D3DXVECTOR3 m_emitPosition;
	list<CParticle*> m_ParticleList;
	list<CParticle*> m_deleteParticleList;
	char m_EmitterName[MAX_NAME];
	int m_count;
	bool m_EmitFlg;	// パーティクルを生成するかのフラグ
	D3DXVECTOR3 m_dir;
};

