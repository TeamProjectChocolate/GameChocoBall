#pragma once
#include "stdafx.h"
#include "Bullet.h"

class CPlayer;


class CEnemyBullet
{
public:
	CEnemyBullet();
	~CEnemyBullet();
	void Initialize();
	void Update();
	void Draw();
	void OnDestroy();
	void Build();
	void BulletPlayerCollision();
	void SetDir(D3DXVECTOR4 dir){
		m_bullet.SetDir(dir);
	}
	void SetPos(D3DXVECTOR3 pos){
		m_bullet.SetPos(pos);
	}
	D3DXVECTOR3 GetPos(){
		return m_bullet.GetPos();
	}
private:
	Bullet m_bullet;

};

