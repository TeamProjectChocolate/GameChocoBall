#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "DirectInput.h"
#include "Light.h"
#include "islntersect.h"
#include "Turn.h"
#include "GameManager.h"
#include "CourceDef.h"
#include "LockOn.h"
#include "Bullet.h"
#include "CBManager.h"

class CLockOn;
class CCBManager;
class CParticleEmitter;
class MoveFloor;
class CPlayer : public C3DImage
{
public:
	CPlayer(){
		strcpy(m_pFileName, "image/Player.X");
		m_pEmitter = nullptr;
	};
	~CPlayer();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("NotNormalMapAnimationFresnelTec");
	}
	void ConfigLight();
	void ReflectionLight(D3DXVECTOR4);
	void SetUpLight();
	void Move();
	void LockOn();
	void BehaviorCorrection();
	void StateManaged();
	void BulletShot();
	void ChocoHit();
	void RollingPlayer();

	void DeleteBullet(Bullet*);
	void ExcuteDeleteBullets();
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
	void Setradius(float radius)
	{
		m_radius = radius;
	}
	bool GetShotflag()
	{
		return Shotflag;
	}
	GAMEEND_ID GetGameState()
	{
		return m_GameState;
	}
	bool GetChocoBall()
	{
		return ChocoBall;
	}
	void SetCBM(CCBManager* CHOCO)
	{
		m_CBManager = CHOCO;
	}
	int GetBusterEnemyNum()
	{
		return BusterEnemyNum;
	}

	//�e�����߂���
	void SetParent(MoveFloor* parent);
	

	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
	CCourceDef GetCourceDef(){
		return m_Courcedef;
	}

private:
	CInterface*	m_pInput;
	CParticleEmitter* m_pEmitter;
	CLight			m_light;
	D3DXVECTOR3		m_lightDir[NUM_DIFFUSE_LIGHT];
	D3DXVECTOR4		m_lightColor[NUM_DIFFUSE_LIGHT];	
	float			_X;
	float			m_radius;
	D3DXVECTOR3		m_initPosition;		//�������W�B
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
	float			m_currentAngleY;	//���݂̕���
	float			m_targetAngleY;		//������������
	float			m_turnSpeed;		//��]���x
	bool			isTurn;				//��]�t���O
	bool            LockOnflag;			//���b�N�I���t���O
	int				m_lockonEnemyIndex;	//���b�N�I�����Ă���G�̃C���f�b�N�X�B
	CLockOn         m_LockOn;			//LockOn�̃C���X�^���X
	CIsIntersect	m_IsIntersect;		//CIsIntersect�̃C���X�^���X

	void UpdateLight();

	CTurn			m_Turn;				//CTurn�̃C���X�^���X
	bool			Shotflag;			//�e�����˂���Ă���̂��̃t���O
	bool            Jumpflag;			//�W�����v�t���O
	GAMEEND_ID		m_GameState = GAMEEND_ID::CONTINUE;
	bool            GamaOverFlag;		//�Q�[���I�[�o
	bool            ChocoBall;			//�`���R�{�[���𗬂��t���O

	float			deadTimer;			//�Q�[���I�[�o�[�܂ł̑ҋ@����
	int             BusterEnemyNum;		//�|�����G�̐�


	D3DXVECTOR3		m_size;	//�v���C���[������o�E���f�B���O�{�b�N�X�̃T�C�Y�B

	CCBManager*		m_CBManager;

	CCourceDef		m_Courcedef;
	D3DXVECTOR3 RV0;
	D3DXMATRIX Rot;
	D3DXVECTOR4 RV1;

	// �e�̔z��
	vector<Bullet*> m_bullets;
	vector<Bullet*> m_Deletebullets;	// �폜���X�g


	//����
	
	bool			m_HitFlag;
	MoveFloor*		parent;
	D3DXVECTOR3		localPosition;
	
	STAGE_ID m_StageID;
};

extern CPlayer* g_player;

namespace tkEngine{
	const D3DXVECTOR3 vec3Zero = { 0.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Right = { 1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Left = { -1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Up = { 0.0f, 1.0f, 0.0f };
	const D3DXVECTOR3 vec3Down = { 0.0f, -1.0f, 0.0f };
	const D3DXVECTOR3 vec3Front = { 0.0f, 0.0f, 1.0f };
	const D3DXVECTOR3 vec3Back = { 0.0f, 0.0f, -1.0f };

	const D3DXVECTOR3 vec3AxisX = { 1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3AxisY = { 0.0f, 1.0f, 0.0f };
	const D3DXVECTOR3 vec3AxisZ = { 0.0f, 0.0f, 1.0f };
}