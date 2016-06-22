#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "ObjectManager.h"
#include "Player.h"


//::落ちる床のクラス::
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

	//プレイヤーとの当たり判定
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
	btRigidBody*		m_rigidBody;		//剛体。
	btCollisionShape*	m_collisionShape;	//コリジョンの形状。
	btDefaultMotionState* m_myMotionState;
	CPlayer*			m_player;
	float m_MaxMove;			// 移動限界量
};