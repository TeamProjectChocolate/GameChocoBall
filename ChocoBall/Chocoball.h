#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "islntersect.h"


class CChocoBall : public C3DImage {
public:
	CChocoBall(){  }
	~CChocoBall(){}

	void Initialize(D3DXVECTOR3 Spos, D3DXVECTOR3 Epos);
	void Update();
	void Draw();
	virtual void SetUpTechnique()override{
		m_pEffect->SetTechnique("NotNormalMapNonAnimationFresnelTec");
	}
	void OnDestroy();

	D3DXVECTOR3 GetPos()
	{
		return m_transform.position;
	}

	//現時点と目的地を渡すとベクトルをセットします。
	//GetVector()で呼び出してください。
	void SetVector(D3DXVECTOR3 Spos, D3DXVECTOR3 Epos){
		m_Vector = Epos - Spos;
	}

	//ベクトルを返すよ！
	D3DXVECTOR3 GetVector()
	{
		return m_Vector;
	}

private:
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*		m_collisionShape;	//コリジョンの形状。
	D3DXVECTOR3				m_EndPosition;		//目的地
	D3DXVECTOR3				m_Vector;			//進行方向を格納。
	D3DXVECTOR3				m_Vector2;
	btDefaultMotionState*	m_myMotionState;
	float					m_life;
	CRigidbody				m_Rigidbody;
	CIsIntersect			m_IsIntersect;
	float					m_radius;
	D3DXVECTOR3				m_moveSpeed;		//移動速度。
	
};