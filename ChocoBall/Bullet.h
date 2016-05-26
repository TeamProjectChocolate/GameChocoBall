#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "islntersect.h"
#include "Rigidbody.h"
#include "LockOn.h"

class CPlayer;
class CEnemyManager;

class Bullet : public C3DImage
{
public:
	Bullet()
	{
		strcpy(m_pFileName, "image/kyu.x");
	};
	~Bullet();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void BulletEnemyCollision();
	void BulletPlayerCollision();
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
private:
	D3DXVECTOR3		m_position;	//弾の座標
	D3DXVECTOR3		m_moveSpeed;//移動速度。
	bool			Shotflag;	//弾が発射されているのかのフラグ
	CPlayer*        m_pPlayer;	//プレイヤーのインスタンス
	CIsIntersect	m_IsIntersect;	//CIsIntersectのインスタンス
	CRigidbody      m_Rigidbody;	//CRigidbodyインスタンス	
	float			m_radius;
	CLockOn          m_LockOn;
	int				m_lockonEnemyIndex;	//ロックオンしている敵のインデックス。
	bool			m_Hitflag;
};

