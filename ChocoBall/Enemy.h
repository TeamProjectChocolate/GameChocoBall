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
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
	float			g_currentAngleY;	//���݂̕���
	float			g_targetAngleY;		//������������
	float			g_turnSpeed;		//��]���x
	bool			isTurn;				//��]�t���O
	CRigidbody		m_Rigidbody;
	bool			flg;
};

