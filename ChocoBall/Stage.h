#pragma once
#include "stdafx.h"
#include "Audio.h"
#include "Player.h"
#include "SceneResult.h"


class CStage
{
public:
	CStage();
	~CStage();
 	virtual void Initialize(CAudio*,STAGE_ID);
	virtual void Update();
	virtual void Draw();
	CAudio* GetAudio(){
		if (m_pAudio == nullptr){
			return nullptr;
		}
		else{
			return m_pAudio;
		}
	}
protected:
	CAudio* m_pAudio;
	STAGE_ID m_Stage_ID = STAGE_ID::STAGE_NONE;
private:
	CPlayer* m_pPlayer;
	CLevelBuilder m_CLevelBuilder;
	bool m_isGameContinue = true;
	GAMEEND_ID m_GameState = GAMEEND_ID::CONTINUE;
};
