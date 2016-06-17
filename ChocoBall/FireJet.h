#pragma once
#include "JetGimmick.h"
#include "Player.h"

class CFireJet :
	public CJetGimmick
{
public:
	CFireJet();
	~CFireJet();
	void Initialize()override;
	void Update()override;
private:
	CPlayer* m_pPlayer;
};

