#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "ObjectManager.h"
#include "Player.h"


//::�����鏰�̃N���X::
class CUpFloor : public C3DImage{
public:
	CUpFloor(){}
	~CUpFloor(){};
	void Initialize(D3DXVECTOR3 pos, D3DXQUATERNION rot);
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

	//�v���C���[�Ƃ̓����蔻��
	bool IsHitPlayer(D3DXVECTOR3 pos, float radius);

	void SetMaxMove(float max){
		m_MaxMove = max;
	}
private:
	D3DXVECTOR4			dimension;
	D3DXVECTOR3			position;
	D3DXVECTOR3			StartPos;
	D3DXVECTOR3			PlayerPos;
	D3DXMATRIX			m_WorldMatrix;
	D3DXMATRIX			m_InvWorld;
	btRigidBody*		m_rigidBody;		//���́B
	btCollisionShape*	m_collisionShape;	//�R���W�����̌`��B
	btDefaultMotionState* m_myMotionState;
	CPlayer*			m_player;
	float m_MaxMove;			// �ړ����E��
};