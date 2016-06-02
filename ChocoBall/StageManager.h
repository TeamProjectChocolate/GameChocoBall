#pragma once
#include "stdafx.h"
#include "Stage.h"
#include "Field.h"
#include "CourceCamera.h"
#include "TestObject2D.h"
#include "EnemyManager.h"


typedef struct STAGE_DATA{
	CHAR StageName[MAX_FILENAME];
	CStage* Stage;
}STAGE_DATA;

typedef struct GENERATION_OBJECT_DATA{
	CHAR ObjectName[MAX_FILENAME];
	PRIORTY priorty;
	bool IsCommon;
	CGameObject* pObject;
public:
	template<class T>
	static T* GenerationObject(){
		T* Obj = new T;
		return Obj;
	}
};

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

private:
	bool m_IsContinue;		// �X�e�[�W�𑱂�����V�ԏꍇ��true,�����łȂ����false
	STAGE_ID m_ContinueStage;	// �Q�[���I�[�o�[�����Ƃ��Ɍ��݂̃X�e�[�W��ێ�����
	STAGE_ID m_NowStage;
	STAGE_ID m_NextStage;

	CStage m_Stage;

	CAudio* m_pAudio;
	//���f�X�g���N�^�ɂČĂяo�����
	void DeleteAll();
};

// �X�e�[�W1�Ŏg�p����I�u�W�F�N�g�̓o�^���i�[�p�\���̔z��
static GENERATION_OBJECT_DATA StageGameObject_1[] = {
	{ "TESTStage3D", PRIORTY::OBJECT3D, false, GENERATION_OBJECT_DATA::GenerationObject<CField>() },
	{ "2DTest", PRIORTY::OBJECT2D_ALPHA, false, GENERATION_OBJECT_DATA::GenerationObject<CTestObject2D>() },
	{ "Number", PRIORTY::OBJECT2D_ALPHA,false,GENERATION_OBJECT_DATA::GenerationObject<CNumber>()},
	{ "Camera" ,PRIORTY::CONFIG,true,GENERATION_OBJECT_DATA::GenerationObject<CCourceCamera>()},
	{ "EnemyManager" ,PRIORTY::PLAYER,false,GENERATION_OBJECT_DATA::GenerationObject<CEnemyManager>()},
	{ "TEST3D", PRIORTY::PLAYER, false, GENERATION_OBJECT_DATA::GenerationObject<CPlayer>() }
};


// �X�e�[�W��ǉ������炱���ɃX�e�[�W�Ŏg�p����I�u�W�F�N�g�z��̃|�C���^���X�e�[�W�̏��Ԃǂ���Ɋi�[���Ă�������
static GENERATION_OBJECT_DATA* StageArray[] = {
	StageGameObject_1
};

static int StageObjectNumArray[] = {
	ARRAYSIZE(StageGameObject_1)
};
