#pragma once
#include "stdafx.h"
#include "Stage.h"
#include "Field.h"
#include "CourceCamera.h"
#include "TestObject2D.h"
#include "EnemyManager.h"


class CStageManager
{
private:
	SINGLETON_DECL(CStageManager)
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();

	//���̃X�e�[�W�ֈڍs����֐�
	void SetNextStage();

	//�X�e�[�W�؂�ւ��֐�
	//������: LPCSTR�^ �ǂ̃X�e�[�W�ɐ؂�ւ��邩
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CStageManager)->ChangeStage(_T("�C���X�^���X�̖��O"));
	//���֐����d�����ߑ��p���Ȃ�����
	void ChangeStage(STAGE_ID);

	void SetIsContinue(bool flg){
		m_IsContinue = flg;
	}
	void SetAudio(CAudio* pAudio){
		m_pAudio = pAudio;
	}
	void SetContinueStage(STAGE_ID id){
		m_ContinueStage = id;
	}
public:
	static int m_ClearNum;
private:
	bool m_IsContinue;		// �X�e�[�W�𑱂�����V�ԏꍇ��true,�����łȂ����false
	STAGE_ID m_ContinueStage;	// �Q�[���I�[�o�[�����Ƃ��Ɍ��݂̃X�e�[�W��ێ�����
	STAGE_ID m_NowStage;
	STAGE_ID m_NextStage;

	CStage* m_pStage = nullptr;

	CAudio* m_pAudio;
	//���f�X�g���N�^�ɂČĂяo�����
	void DeleteAll();
};
