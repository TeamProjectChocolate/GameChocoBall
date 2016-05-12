#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"

class CEnemy : public C3DImage
{
public:
	CEnemy(){
		strcpy(m_pFileName, "image/kyu.x");
	};
	~CEnemy();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void OnDestroy();
	void Build();
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
	void Setradius(float radius)
	{
		m_radius = radius;
	}
private:
	D3DXVECTOR3		m_position;
	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;		//移動速度。
	float			g_currentAngleY;	//現在の方向
	float			g_targetAngleY;		//向きたい方向
	float			g_turnSpeed;		//回転速度
	bool			isTurn;				//回転フラグ
	CRigidbody		m_Rigidbody;
	bool			flg;
};

