#pragma once
#include "GraphicsDevice.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "CBManager.h"

#define ENEMYNUM 20

class CMainScene:public CScene{
public:
	CMainScene();
	~CMainScene();
	void Initialize();
	void Update();
	void Draw();
private:
	CPlayer m_Player;
	CEnemy m_Enemy;	//“G‚Ì•Ï”B
	Bullet m_Bullet;
};