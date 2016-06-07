#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Player.h"


class MoveFloor:public C3DImage{
public:
	MoveFloor();
	~MoveFloor();
	void Initialize(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	void Update()override;
	void Draw()override;
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	void SetPos(D3DXVECTOR3 pos){
		position = pos;
	}
	D3DXVECTOR3 GetPos(){
		return position;
	}

	

	//プレイヤーとの当たり判定
	bool IsHitPlayer(D3DXVECTOR3 pos, float radius);

	D3DXVECTOR3 GetMoveSpeed(){
		return m_MoveSpeed;
	}
private:
	D3DXVECTOR4			dimension;
	D3DXVECTOR3			position;
	D3DXMATRIX			m_WorldMatrix;
	D3DXMATRIX			m_InvWorld;
	CPlayer*			m_player;
	btRigidBody*		m_rigidBody;
	btCollisionShape*	m_collisionShape;	//コリジョンの形状。
	btDefaultMotionState* m_myMotionState;
	D3DXVECTOR3			StartPos;
	D3DXVECTOR3			PlayerPos;
	D3DXVECTOR3			m_MoveSpeed;
};