#pragma once
#include "GraphicsDevice.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "CBManager.h"
#include "LevelBuilder.h"

#define ENEMYNUM 20

class CMainScene:public CScene{
public:
	CMainScene();
	~CMainScene();
	void Initialize();
	void Update();
	void Draw();
private:
	CEnemy m_Enemy;	//“G‚Ì•Ï”B
	Bullet m_Bullet;
};