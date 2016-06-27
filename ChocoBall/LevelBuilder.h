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
	btBoxShape*	m_GhostShape[MaxCollision];	//�����蔻�肾��������R���W�����`��B
	btGhostObject*		m_ghostObject[MaxCollision];		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	std::vector<CCBManager*>	m_chocoballMgrList;			//�`���R�{�[���}�l�[�W���̃��X�g�B
	STAGE_ID m_IsStage;
	int m_ChocoWallNum;
	int m_FireJetNum;
};