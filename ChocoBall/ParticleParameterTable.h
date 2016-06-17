#pragma once
#include "stdafx.h"


// �p�[�e�B�N�������p�����[�^�\���̂̒�`
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
	int EmitNum;				// 1�t���[���ɔ����������
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


// �V�����p�����[�^��ݒ肵���炱�̗񋓑̂ɒǉ����邱��
enum PARTICLE_TYPE{FIRE = 0,PORIGON,FIREGIMMICK};


// �p�[�e�B�N���̃p�����[�^
// �V�����p�[�e�B�N���𐶐������炱���Ɉȉ��̂悤�ȏ������Œǉ����Ă�������
// ���ǉ������\���̂̃|�C���^����ԉ��̃|�C���^�[�z��ɒǉ�����̂�Y��Ȃ�����

// �R���オ�鉊
static SParticleEmitParameter Param_Fire = {
	"image/PRT_Fire.png",	//�e�N�X�`���̃t�@�C����
	D3DXVECTOR3(0.0f, 1.0f, 0.0f),		// �����x�B
	1.5f,							// �����B�P�ʂ͕b�B
	0.001f,							// �������ԁB�P�ʂ͕b�B
	1,								// 1�t���[���ɔ����������
	0.5f,							// �p�[�e�B�N���̕��B
	0.5f,							// �p�[�e�B�N���̍����B
	D3DXVECTOR3(0.3f, 0.0f, 0.3f),		// �����ʒu�̃����_�����B
	D3DXVECTOR3(0.3f, 0.0f, 0.3f),		// �����x�̃����_�����B
	D3DXVECTOR3(0.006f, 0.0f, 0.006f),	// ���x�̐ϕ��̂Ƃ��̃����_�����B
	{	// UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
		D3DXVECTOR4(0.0f, 0.0f, 0.25f, 0.5f),
		D3DXVECTOR4(0.25f, 0.0f, 0.5f, 0.5f),
		D3DXVECTOR4(0.5f, 0.0f, 0.75f, 0.5f),
		D3DXVECTOR4(0.75f, 0.0f, 1.0f, 0.5f),
	},
	4,									// UV�e�[�u���̃T�C�Y�B
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d�́B
	true,							// ���ʂƂ��Ƀt�F�[�h�A�E�g����H
	1.5f,							// �t�F�[�h���鎞�ԁB
	1.0f,							// �����A���t�@�l�B
	true,							// �r���{�[�h�H
	2.0f,							// �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	1,								// �����������A1���Z�����B
};

// ���F�̓���
static SParticleEmitParameter Param_Porigon = {
	"image/test.png",	//�e�N�X�`���̃t�@�C����
	D3DXVECTOR3(0.0f, 1.0f, 0.0f),		// �����x�B
	1.5f,							// �����B�P�ʂ͕b�B
	0.001f,							// �������ԁB�P�ʂ͕b�B
	1,								// 1�t���[���ɔ����������
	0.5f,							// �p�[�e�B�N���̕��B
	0.5f,							// �p�[�e�B�N���̍����B
	D3DXVECTOR3(0.3f, 0.0f, 0.3f),		// �����ʒu�̃����_�����B
	D3DXVECTOR3(0.3f, 0.0f, 0.3f),		// �����x�̃����_�����B
	D3DXVECTOR3(0.006f, 0.0f, 0.006f),	// ���x�̐ϕ��̂Ƃ��̃����_�����B
	{	// UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
		D3DXVECTOR4(0.0f, 0.0f, 0.25f, 0.5f),
		D3DXVECTOR4(0.25f, 0.0f, 0.5f, 0.5f),
		D3DXVECTOR4(0.5f, 0.0f, 0.75f, 0.5f),
		D3DXVECTOR4(0.75f, 0.0f, 1.0f, 0.5f),
	},
	4,									// UV�e�[�u���̃T�C�Y�B
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d�́B
	true,							// ���ʂƂ��Ƀt�F�[�h�A�E�g����H
	1.5f,							// �t�F�[�h���鎞�ԁB
	1.0f,							// �����A���t�@�l�B
	true,							// �r���{�[�h�H
	2.0f,							// �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	1,								// �����������A1���Z�����B
};

// �R���オ�鉊
static SParticleEmitParameter Param_FireGimmick = {
	"image/PRT_Fire.png",	//�e�N�X�`���̃t�@�C����
	D3DXVECTOR3(0.0f, 0.0f, 1.0f),		// �����x�B
	4.0f,							// �����B�P�ʂ͕b�B
	0.0f,							// �������ԁB�P�ʂ͕b�B
	4,								// 1�t���[���ɔ����������
	0.5f,							// �p�[�e�B�N���̕��B
	0.5f,							// �p�[�e�B�N���̍����B
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �����ʒu�̃����_�����B
	D3DXVECTOR3(0.15f, 0.15f, 0.0f),		// �����x�̃����_�����B
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// ���x�̐ϕ��̂Ƃ��̃����_�����B
	{	// UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
		D3DXVECTOR4(0.0f, 0.0f, 0.25f, 0.5f),
		D3DXVECTOR4(0.25f, 0.0f, 0.5f, 0.5f),
		D3DXVECTOR4(0.5f, 0.0f, 0.75f, 0.5f),
		D3DXVECTOR4(0.75f, 0.0f, 1.0f, 0.5f),
	},
	4,									// UV�e�[�u���̃T�C�Y�B
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d�́B
	true,							// ���ʂƂ��Ƀt�F�[�h�A�E�g����H
	0.5f,							// �t�F�[�h���鎞�ԁB
	1.0f,							// �����A���t�@�l�B
	true,							// �r���{�[�h�H
	2.0f,							// �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	1,								// �����������A1���Z�����B
};


// �p�����[�^�[�\���̂̃|�C���^�z��
// ���p�����[�^�[��ǉ������炱���ɒǉ������\���̂̃|�C���^���i�[���邱��
static SParticleEmitParameter* ParticleParamPT_Array[] = { 
	&Param_Fire,
	&Param_Porigon,
	&Param_FireGimmick
};
