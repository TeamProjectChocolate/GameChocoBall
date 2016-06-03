#pragma once
#include "Scene.h"
#include "ResultBack.h"
#include "ResultSelect.h"
#include "ResultCursor.h"
#include "Score.h"

#define TIMEBONUS 10
#define ENEMY_BONUS 20

class CSceneResult : 
	public CScene
{
public:
	CSceneResult();
	~CSceneResult();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	bool GetIsEnd(){
		return m_IsEnd;
	}
	void SetTime(const int time){ m_time = time; };
	void SetEnemyCounter(const int enemycounter){ m_enemycounter = enemycounter; };
private:
	CResultBack m_rBack;
	CResultSelect m_rSelect[2];
	CResultCursor m_rCursor;
	CScoreCalc m_Score;
	CNumber m_Number;
	bool m_IsEnd;
	int m_time;
	int m_enemycounter;
};