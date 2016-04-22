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
	HRESULT CreateSprite();
private:
	LPD3DXSPRITE m_pSprite;	//スプライト
	CPlayer m_Player;
	CAudio* m_pAudio;
};