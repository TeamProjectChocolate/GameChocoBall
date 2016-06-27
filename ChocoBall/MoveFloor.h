#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Player.h"
#include "Audio.h"


class MoveFloor : public C3DImage{
public:
	MoveFloor();
	~MoveFloor();
	void Initialize(D3DXVECTOR3 pos, D3DXQUATERNION rot, D3DXVECTOR3 scale);
	void Update()override;
	void Draw()override;
	virtual void SetUpTechnique()override{
		m_pEffect->SetTechnique("NotNormalMapNonAnimationFresnelShadowTec");
	}
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	void SetPos(D3DXVECTOR3 pos){
		position = pos;
	}
	D3DXVECTOR3 GetPos(){
		return position;
	}

	void SetMaxMove(float maxmove){
		MaxMove = maxmove;
	}

	//�v���C���[�Ƃ̓����蔻��
	bool IsHitPlayer(D3DXVECTOR3 pos, float radius);

	D3DXVECTOR3 GetMoveSpeed(){
		return m_MoveSpeed;
	}
	void SetDirection(D3DXVECTOR3 dir){
		D3DXVec3Normalize(&m_dir, &dir);
	}

	D3DXVECTOR3 GetDirection(){
		return m_dir;
	}

	void SetAudio(CAudio* audio)
	{
		m_pAudio = audio;
	}
private:
	D3DXVECTOR4			dimension;
	D3DXVECTOR3			position;
	D3DXMATRIX			m_WorldMatrix;
	D3DXMATRIX			m_InvWorld;
	CPlayer*			m_player;
	btRigidBody*		m_rigidBody;
	btCollisionShape*	m_collisionShape;	//�R���W�����̌`��B
	btDefaultMotionState* m_myMotionState;
	D3DXVECTOR3			StartPos;
	D3DXVECTOR3			PlayerPos;
	D3DXVECTOR3			m_MoveSpeed;
	CAudio*				m_pAudio;
	float				MaxMove;
	int m_state;
	enum state{
		move_flont,
		move_back,
		move_none
	};
	D3DXVECTOR3 m_dir;
};