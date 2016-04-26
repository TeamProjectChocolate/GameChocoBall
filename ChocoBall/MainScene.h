#pragma once
#include "GraphicsDevice.h"
#include "Player.h"

class CAudio;

class CMainScene{
public:
	CMainScene();
	~CMainScene();
	void Initialize();
	void Update();
	void Draw();
private:
	CPlayer m_Player;
	CAudio* m_pAudio;
};