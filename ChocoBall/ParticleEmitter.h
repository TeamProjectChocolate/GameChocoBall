#pragma once
#include "GameObject.h"
#include "CourceCamera.h"
#include "Particle.h"

#define MAX_NAME 256

// �p�[�e�B�N�������p�����[�^
typedef struct SParticleEmitParameter{
	void Init(){
		memset(this, 0, sizeof(SParticleEmitParameter));
		initAlpha = 0.0f;
		uvTableSize = 1;
		brightness = 1.0f;
		isBillboard = true;
	};
	const char* texturePath;	// �e�N�X�`���̃t�@�C���p�X
	D3DXVECTOR3 initVelocity;	// �����x
	float life;					// ����
	float intervalTime;			// ��������
	float w;					// �p�[�e�B�N���̕�
	float h;					// �p�[�e�B�N���̍���
	D3DXVECTOR3 initPositionRandomMargin;	// �����ʒu�̃����_����
	D3DXVECTOR3 initVelocityVelocityRandomMargin;	// �����x�̃����_����
	D3DXVECTOR3 addVelocityRandomMargin;			// ���x�̐ϕ��̂Ƃ��̃����_����
	D3DXVECTOR4 uvTable[4];		// uv�e�[�u���B�ő�4�܂ŕۑ��ł���Bx�������u�By�������v�Bz���E����u�Bw���E����v�ɂȂ�B
	int uvTableSize;			// uv�e�[�u���̃T�C�Y
	D3DXVECTOR3 gravity;		// �d��
	bool isFade;				// ���ʂƂ��Ƀt�F�[�h�A�E�g���邩
	float fadeTime;				// �t�F�[�h���鎞��
	float initAlpha;			// �����A���t�@�l
	bool isBillboard;			// �r���{�[�h�H
	float brightness;			// �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������ӂ��
	int alphaBlendMode;			// �����������A1���Z����
};

// �p�[�e�B�N���̔����@
class CParticleEmitter:public CGameObject
{
public:
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
	void SetEmitterName(LPCSTR name){
		CH_ASSERT(strlen(name) < MAX_NAME);
		strcpy(m_EmitterName, name);
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
};

