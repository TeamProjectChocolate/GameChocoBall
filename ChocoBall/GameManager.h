#pragma once

#include "stdafx.h"
#include "Scene.h"

#include "Assert.h"

#define SCENENAME_MAX 255

typedef struct SCENE_DATA{
	CHAR SceneName[SCENENAME_MAX + 1];
	CScene* Scene;
}SCENE_DATA;

class CGameManager
{
	SINGLETON_DECL(CGameManager)
public:
	//�������œn����Scene�̃C���X�^���X��GameManager�N���X�ɒǉ�����֐�
	//������:CScene*�^ �ǉ�����ACScene�N���X���p�������N���X�̃|�C���^ 
	//		 LPCSTR�^ �C���X�^���X�̖��O
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CGameManager)->AddScene(&m_TitleScene,_T("�C���X�^���X�̖��O"));
	//���C���X�^���X�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���C���X�^���X�̖��O��255�����ȓ��Ƃ��Ă�������
	//�����̊֐��Ő��������C���X�^���X��new�Ő������Ă���ꍇ�́ACGameManager�N���X�̊O���ŕK��delete���Ă�������
	void AddScene(CScene*,LPCSTR);

	template<class T>
	//�w�肵��Scene�̃C���X�^���X��������������֐�
	//������: LPCSTR�^ �C���X�^���X�̖��O
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CGameManager)->GenerationObject<�����������V�[���̃N���X��>(_T("�C���X�^���X�̖��O"));
	//���C���X�^���X�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���C���X�^���X�̖��O��255�����ȓ��Ƃ��Ă�������
	//�����̊֐��Ő��������C���X�^���X��CGameManager�N���X�̊O����delete���Ȃ�����
	void GenerationScene(LPCSTR SceneName){
		CH_ASSERT(strlen(SceneName) <= SCENENAME_MAX);
		if (FindScene(SceneName) != nullptr){
			MessageBox(NULL, "���̖��O��Scene�C���X�^���X�͂��łɓo�^����Ă��܂�", 0, 0);
			return;
		}
		T* Scene = new T;
		Scene->ActiveManagerNewFlg();	// ObjectManager�N���X����new�������߁A�t���O��true�ɂ���
		SCENE_DATA SceneData;
		strcpy(SceneData.SceneName, SceneName);
		SceneData.Scene = Scene;
		this->Add(&SceneData);
	}

	//GameManager�N���X�ɓo�^����Ă���Scene�N���X�̃C���X�^���X�𖼑O�Ō�������֐�
	//������: LPCSTR�^ �C���X�^���X�̖��O
	//�Ԃ�l: CScene*�^ �������̖��O�ƈ�v�����I�u�W�F�N�g�̃|�C���^(�ǂꂩ���)
	//�Ăяo����: SINSTANCE(CGameManager)->FindScene(_T("�C���X�^���X�̖��O"));
	//���֐����d�����ߑ��p���Ȃ�����
	CScene* FindScene(LPCSTR);

	//�V�[���؂�ւ��֐�
	//������: LPCSTR�^ �ǂ̃V�[���ɐ؂�ւ��邩
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CGameManager)->ChangeScene(_T("�C���X�^���X�̖��O"));
	//���֐����d�����ߑ��p���Ȃ�����
	void ChangeScene(LPCSTR);
	void SetNextScene();
	void Update();
	void Draw();
	LPCSTR GetScene(){
		return m_NowSceneName;
	}

	void SetAudio(CAudio* audio){
		m_pAudio = audio;
	}
private:
	vector<SCENE_DATA*> m_Scenes;
	CScene* m_NowScene = nullptr;
	void Initialize();
	void Add(SCENE_DATA*);
	char m_NowSceneName[SCENENAME_MAX + 1];
	char m_NextSceneName[SCENENAME_MAX + 1];
	CAudio* m_pAudio;

	//vector�ɓo�^���ꂽ�v�f�����ׂč폜����֐�
	//���f�X�g���N�^�ɂČĂяo�����
	void DeleteAll();
};

