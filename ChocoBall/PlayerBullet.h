#pragma once
#include "stdafx.h"
#include "Bullet.h"
#include "LockOn.h"

class CEnemyManager;

class CPlayerBullet
{
public:
	CPlayerBullet();
	~CPlayerBullet();
	void Initialize();
	void Update();
	void Draw();
	void OnDestroy();
	void Build();
	void SetDir(D3DXVECTOR4 dir){
		m_bullet.SetDir(dir);
	}
	void BulletEnemyCollision();
	void BulletBlockCollision();
	void SetPos(D3DXVECTOR3 pos){
		m_bullet.SetPos(pos);
	}
	D3DXVECTOR3 GetPos(){
		return m_bullet.GetPos();
	}
private:
	CLockOn          m_LockOn;
	int				m_lockonEnemyIndex;	//ロックオンしている敵のインデックス。
	CEnemyManager* m_pEnemyManager;
	CBuildBlock* m_pBlockManager;
	Bullet m_bullet;
};

