#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "DirectInput.h"
#include "BulletPhysics.h"

class CEnemy : public C3DImage
{
public:
	CEnemy(){
		m_pInput = nullptr;
		m_ghostObject = nullptr;
		m_collisionShape = nullptr;
		m_rigidBody = nullptr;
		m_myMotionState = nullptr;
		strcpy(m_pFileName, "image/kyu.x");
	};
	~CEnemy();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
private:
	CDirectInput* m_pInput;

	//ここからBulletPhysicsで衝突判定を行うためのメンバ変数。
	btGhostObject*		m_ghostObject;		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	btSphereShape*		m_collisionShape;	//!<コリジョン形状。
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
	D3DXVECTOR3		m_position;
	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;		//移動速度。
	float			g_currentAngleY;	//現在の方向
	float			g_targetAngleY;		//向きたい方向
	float			g_turnSpeed;		//回転速度
	bool			isTurn;				//回転フラグ
};

