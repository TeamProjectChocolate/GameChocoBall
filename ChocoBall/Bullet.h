#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "islntersect.h"
#include "Rigidbody.h"
#include "LockOn.h"
#include "BuildBlock.h"
#include "EnemyManager.h"

#define BULLET_LENG 20.0f


class  CPlayer;

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
	void BulletEnemyCollision();

	void BulletBlockCollision();
	void SetUpTechnique()override
	{
		m_pEffect->SetTechnique("NotNormalMapBasicTec");//Textureが無いのでセットテクニックをオーバーライド
	};
	void OnDestroy();
	void Build();
	bool GetHitflag()
	{
		return m_Hitflag;
	}
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

	CLockOn          m_LockOn;
	int				m_lockonEnemyIndex;	//ロックオンしている敵のインデックス。
	bool			m_Hitflag;
	D3DXVECTOR4 m_dir;
	CEnemyManager* m_pEnemyManager;
	CBuildBlock* m_pBlockManager;
	float m_Speed;//弾のスピード
};

