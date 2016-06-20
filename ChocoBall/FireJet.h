#pragma once
#include "JetGimmick.h"
#include "Player.h"
#include "Vibration.h"

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
	CVibration m_vibration;
	COURCE_BLOCK m_TargetCource;
};

