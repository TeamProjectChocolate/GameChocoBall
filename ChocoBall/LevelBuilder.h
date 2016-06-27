#pragma once
#include "BulletPhysics.h"
#include "EnemyBase.h"
#include "Audio.h"
#define MaxCollision 100

class CCBManager;

class CLevelBuilder{
public:
	CLevelBuilder();
	~CLevelBuilder();
	void Build(CAudio*);
	void SetIsStage(STAGE_ID now){
		m_IsStage = now;
	}
private:
	btBoxShape*	m_GhostShape[MaxCollision];	//当たり判定だけがあるコリジョン形状。
	btGhostObject*		m_ghostObject[MaxCollision];		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	std::vector<CCBManager*>	m_chocoballMgrList;			//チョコボールマネージャのリスト。
	STAGE_ID m_IsStage;
	int m_ChocoWallNum;
	int m_FireJetNum;
};