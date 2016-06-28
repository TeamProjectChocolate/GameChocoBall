#pragma once
#include "GameObject.h"
#include "CourceCamera.h"
#include "Particle.h"
#include "ParticleParameterTable.h"
#include "ObjectManager.h"
#include "Player.h"

#define MAX_NAME 256

// �p�[�e�B�N���̔����@
class CParticleEmitter:public CGameObject
{
public:
	static CParticleEmitter* EmitterCreate(LPCSTR EmitterName, PARTICLE_TYPE type,D3DXVECTOR3 pos,CCamera* pcamera,STAGE_ID Id,bool flg){
		CParticleEmitter* pEmitter = SINSTANCE(CObjectManager)->GenerationObject<CParticleEmitter>(EmitterName, PRIORTY::EMITTER, false);
		pEmitter->SetCamera(pcamera);
		pEmitter->SetEmitParameter(reinterpret_cast<SParticleEmitParameter*>(ParticleParamPT_Array[type]));
		pEmitter->SetEmitterName(EmitterName);
		pEmitter->SetEmitPos(pos);
		pEmitter->SetEmitFlg(flg);
		pEmitter->SetStageID(Id);
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
	SParticleEmitParameter* GetEmitParameter(){
		return m_param;
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
	bool GetEmitFlg(){
		return m_EmitFlg;
	}
	void SetDirection(D3DXVECTOR3 dir){
		m_dir = dir;
	}
	D3DXVECTOR3 GetDirection(){
		return m_dir;
	}
	D3DXVECTOR3 GetTailPos(){
		return *m_TailPosition;
	}
	bool GetResidual(){
		return m_Residual;
	}
	void SetStageID(STAGE_ID id){
		m_Stage_ID = id;
	}
	int GetCourceNo(){
		return m_CurrentCourceNo;
	}
	int GetPlayerCourceNo(){
		return m_NowPlayerCourceNo;
	}
	void SetCourceLange(int lange){
		m_CourceLange = lange;
	}
	int GetCourceLange(){
		return m_CourceLange; 
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
	char m_ParticleName[MAX_NAME];
	int m_count;
	bool m_EmitFlg;	// �p�[�e�B�N���𐶐����邩�̃t���O
	D3DXVECTOR3 m_dir;
	int m_CurrentCourceNo;
	int m_NowPlayerCourceNo;
	CCourceDef m_CourceDef;
	CPlayer* m_pPlayer;
	D3DXVECTOR3* m_TailPosition;	// �Ō�ɐ��������v���~�e�B�u�̃|�W�V������ǐՂ��邽�߂̃|�C���^
	CParticle* m_pTailParticle;		// �Ō�ɐ��������p�[�e�B�N���̃|�C���^
	bool m_Residual;			// �Ō�ɐ��������p�[�e�B�N�����c�����Ă��邩
	int m_CourceLange;			// �v���C���[�ƃp�[�e�B�N���̔����ʒu���ǂꂭ�炢����Ă���Δ��������Ȃ���
private:
	STAGE_ID m_Stage_ID;
};

