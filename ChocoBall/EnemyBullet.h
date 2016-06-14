#pragma once
#include "stdafx.h"
#include "Bullet.h"


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
		m_enemybullet.SetDir(dir);
	}
	void SetPos(D3DXVECTOR3 pos){
		m_enemybullet.SetPos(pos);
	}
	D3DXVECTOR3 GetPos(){
		return m_enemybullet.GetPos();
	}
	void SetBulletSpeed(float s){
		m_enemybullet.SetBulletSpeed(s);
	}
	
private:
	Bullet m_enemybullet;
};

