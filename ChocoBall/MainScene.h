#pragma once
#include "GraphicsDevice.h"
#include "Scene.h"
#include "Player.h"

class CMainScene:public CScene{
public:
	CMainScene();
	~CMainScene();
	void Initialize();
	void Update();
	void Draw();
private:
	CPlayer m_Player;
};