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
#include "PlayerBullet.h"
#include "CBManager.h"
#include "Vibration.h"
#include "CourceCamera.h"
#include "Audio.h"

class CLockOn;
class CCBManager;
class CParticleEmitter;
class MoveFloor;

enum PLAYER_STATE{Wait = 0, Walk, Jump };
class CPlayer : public C3DImage
{
public:
	CPlayer(){
		strcpy(m_pFileName, "image/Player.X");
		m_pEmitter = nullptr;
		m_pCamera = nullptr;
		parent = nullptr;
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

	void DeleteChocoBall(CCBManager*);
	void ExcuteDeleteChocoBall();

	void DeleteBullet(CPlayerBullet*);
	void ExcuteDeleteBullets();
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
	void EnemyBulletHit( D3DXVECTOR3 moveDir );
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
		m_CBManager.push_back(CHOCO);
	}
	int GetBusterEnemyNum()
	{
		return BusterEnemyNum;
	}

	//�e�����߂���
	void SetParent(MoveFloor* parent);

	MoveFloor* GetParent(){
		return parent;
	}
	

	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
	CCourceDef* GetCourceDef(){
		return &m_Courcedef;
	}

	bool GetGameover()
	{
		return GamaOverFlag;
	}
	void RequestGameOver()
	{
		m_GameState = GAMEEND_ID::OVER;
	}
	bool IsVibration() ;
	
	void SetAudio(CAudio* audio){
		m_pAudio = audio;
	}
private:
	CInterface*	m_pInput;
	CParticleEmitter* m_pEmitter;
	CParticleEmitter* m_pEmitter2;
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
	bool            GamaOverFlag;		//�Q�[���I�[�o�[
	bool            ChocoBall;			//�`���R�{�[���𗬂��t���O

	float			deadTimer;			//�Q�[���I�[�o�[�܂ł̑ҋ@����
	int             BusterEnemyNum;		//�|�����G�̐�

	float m_JumpParticleTime;						//�W�����v�����n���̃p�[�e�B�N���������������鎞��
	float m_JumpParticleTimer;						//�W�����v�����n���̃p�[�e�B�N�����𔭐������鎞�Ԃ̃J�E���^�[

	//float m_GunParticleTime;						//�e���ˎ��̃p�[�e�B�N���������������鎞��
	//float m_GunParticleTimer;						//�e���ˎ��̃p�[�e�B�N�����𔭐������鎞�Ԃ̃J�E���^�[

	bool m_PreviousJumpFlag;			//�p�[�e�B�N�����W�����v�̒��n���ɔ��������邽�߂̃t���O

	int BulletShotInterval;			//�e�𔭎˂���Ԋu�̎���

	D3DXVECTOR3		m_size;	//�v���C���[������o�E���f�B���O�{�b�N�X�̃T�C�Y�B

	list<CCBManager*> m_CBManager;
	list<CCBManager*> m_DeleteChocoBall;

	CCourceDef		m_Courcedef;
	D3DXVECTOR3 RV0;
	D3DXMATRIX Rot;
	D3DXVECTOR4 RV1;

	// �e�̔z��
	vector<CPlayerBullet*> m_bullets;
	vector<CPlayerBullet*> m_Deletebullets;	// �폜���X�g


	//����
	
	bool			m_HitFlag;
	MoveFloor*		parent;
	D3DXVECTOR3		localPosition;


	//
	STAGE_ID m_StageID;
	bool m_MoveFlg;
	CVibration m_vibration;
	CCourceCamera* m_pCamera;

	CAudio* m_pAudio;//SE�g�p
	int m_NowCourceNo;
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

static double AnimationTime[] = {
	-1.0,
	20.0f/30.0f
};