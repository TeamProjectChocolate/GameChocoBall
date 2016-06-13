#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "islntersect.h"
#include "Rigidbody.h"
#include "BuildBlock.h"

#define BULLET_LENG 20.0f


class Bullet : public C3DImage
{
public:
	Bullet()
	{
		strcpy(m_pFileName, "image/ball.x");
	};
	~Bullet();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override
	{
		m_pEffect->SetTechnique("NormalMapBasicTec");//Textureが無いのでセットテクニックをオーバーライド
	};
	void OnDestroy();
	void Build();
	void SetDir(D3DXVECTOR4 dir){
		m_dir = dir;
	}
	void SetBulletSpeed(float Speed)
	{
		m_Speed = Speed;
	}
private:
	D3DXVECTOR3		m_position;	//弾の座標
	D3DXVECTOR3		m_moveSpeed;//移動速度。
	bool			Shotflag;	//弾が発射されているのかのフラグ
	CIsIntersect	m_IsIntersect;	//CIsIntersectのインスタンス
	float			m_radius;
	D3DXVECTOR4 m_dir;

	float m_Speed;//弾のスピード
};

