#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "BulletPhysics.h"
#include "Assert.h"

#define OBJECTNAME_MAX 255

// �Q�[���I�u�W�F�N�g�\����
typedef struct OBJECT_DATA{
	CHAR objectname[OBJECTNAME_MAX + 1];	// ��������I�u�W�F�N�g��
	CGameObject* object;	// �Q�[���I�u�W�F�N�g�̃|�C���^
	short priority;			// ���s�D��x(�������������قǗD��x�������@�ŏ��l�F0)
}OBJECT_DATA;

class CObjectManager
{
	SINGLETON_DECL(CObjectManager)
public:

	template<class T>
	//�w�肵���I�u�W�F�N�g��������������֐�(�D��x���w�肵�����ꍇ)
	//������: LPCSTR�^ �C���X�^���X�̖��O 
	//		  PRIORTY�^ �X�V�D��x(0���ŏ��A�������傫���قǗD��x���Ⴂ)
	//		  bool�^ �풓�t���O�w��(true�Ȃ�V�[���؂�ւ����ɍ폜����Ȃ�)
	//�Ԃ�l: T*�^ ���������N���X�̃I�u�W�F�N�g��ԋp
	//�Ăяo����: SINSTANCE(CObjectManager)->GenerationObject<�����������N���X��>(_T("�C���X�^���X�̖��O"),0,false);
	//���C���X�^���X�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���C���X�^���X�̖��O��255�����ȓ��Ƃ��Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���K��CObjectManager�N���X��DeleteGameObject�֐����Ăяo���čs������
	T* GenerationObject(LPCSTR ObjectName,PRIORTY priorty,bool common){
		T* Object = new T;
		Object->ActiveManagerNewFlg();	// ObjectManager�N���X����new�������߁A�t���O��true�ɂ���
		Object->SetCommon(common);
		if (priorty > PRIORTY::MAX_PRIORTY){
			priorty = PRIORTY::MAX_PRIORTY;
		}
		this->Add(Object, ObjectName,priorty);
		return Object;
	}

	template<class T>
	//�w�肵���I�u�W�F�N�g��������������֐�(�D��x�Ȃ��F�����I�ɗD��x�͍Œ�ɂȂ�܂�)
	//������: LPCSTR�^ �C���X�^���X�̖��O
	//		  bool�^ �풓�t���O�w��(true�Ȃ�V�[���؂�ւ����ɍ폜����Ȃ�)
	//�Ԃ�l: T*�^ ���������N���X�̃I�u�W�F�N�g��ԋp
	//�Ăяo����: SINSTANCE(CObjectManager)->GenerationObject<�����������N���X��>(_T("�C���X�^���X�̖��O"),false);
	//���C���X�^���X�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���C���X�^���X�̖��O��255�����ȓ��Ƃ��Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���K��CObjectManager�N���X��DeleteGameObject�֐����Ăяo���čs������
	T* GenerationObject(LPCSTR ObjectName,bool common){
		T* Object = new T;
		Object->ActiveManagerNewFlg();	// ObjectManager�N���X����new�������߁A�t���O��true�ɂ���
		Object->SetCommon(common);
		PRIORTY priorty = PRIORTY::MAX_PRIORTY;
		this->Add(Object,ObjectName ,priorty);
		return Object;
	}

	//���łɐ�������Ă���I�u�W�F�N�g���}�l�[�W���[�N���X�ɓo�^����֐�(�D��x���w�肵�����ꍇ)
	//������: CGameObject*�^ �o�^����GameObject�̃|�C���^
	//		�@short�^ �X�V�D��x(0���ŏ��A�������傫���قǗD��x���Ⴂ)
	//		  bool�^ �풓�t���O�w��(true�Ȃ�V�[���؂�ւ����ɍ폜����Ȃ�)
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->AddObject(�ǉ��������C���X�^���X�̃|�C���^,_T("�C���X�^���X�̖��O"),0);
	//���C���X�^���X�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���C���X�^���X�̖��O��255�����ȓ��Ƃ��Ă�������
	//�����̊֐��œo�^�����C���X�^���X��new�Ő������Ă���ꍇ�́A�K��CObjectManager�N���X��DeleteGameObject�֐����Ăяo�������
	//  CObjectManager�N���X�̊O���ł������delete���Ă�������
	void AddObject(CGameObject*,LPCSTR, PRIORTY,bool);

	//���łɐ�������Ă���I�u�W�F�N�g���}�l�[�W���[�N���X�ɓo�^����֐�(�D��x�Ȃ��F�����I�ɗD��x�͍Œ�ɂȂ�܂�)
	//������: CGameObject*�^ �o�^����GameObject�̃|�C���^
	//		  bool�^ �풓�t���O�w��(true�Ȃ�V�[���؂�ւ����ɍ폜����Ȃ�)
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->AddObject(�ǉ��������C���X�^���X�̃|�C���^,_T("�C���X�^���X�̖��O"));
	//���C���X�^���X�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���C���X�^���X�̖��O��255�����ȓ��Ƃ��Ă�������
	//�����̊֐��œo�^�����C���X�^���X��new�Ő������Ă���ꍇ�́A�K��CObjectManager�N���X��DeleteGameObject�֐����Ăяo�������
	//  CObjectManager�N���X�̊O���ł������delete���Ă�������
	void AddObject(CGameObject*, LPCSTR,bool);

	template<class T>
	//ObjectManager�N���X�ɓo�^����Ă���GameObject�̃C���X�^���X�𖼑O�Ō�������֐�
	//������: LPCSTR�^ �C���X�^���X�̖��O
	//�Ԃ�l: CGameObject*�^ �������̖��O�ƈ�v�����I�u�W�F�N�g�̃|�C���^(�ǂꂩ���)
	//�Ăяo����: SINSTANCE(CObjectManager)->FindGameObject<�����������N���X��>(_T("�C���X�^���X�̖��O"));
 	//���������O����v�����ꍇ�ǂꂩ����Ԃ���܂�
	//���m���ɂ��̃C���X�^���X���擾�������ꍇ�̓v���O���}�[��������ƃ��j�[�N�Ȗ��O�œo�^���Ă�������
	//���֐����d�����ߑ��p���Ȃ�����
	T* FindGameObject(LPCSTR ObjectName)
	{
		int size = m_GameObjects.size();
		for (int idx = 0; idx < size; idx++){
			if (!strcmp(m_GameObjects[idx]->objectname,ObjectName)){
				return (T*)m_GameObjects[idx]->object;
			}
		}
		//MessageBox(NULL, "�I�u�W�F�N�g���o�^����Ă��܂���", 0, 0);
		return nullptr;
	}

	//Objectmanager�N���X�ɓo�^����Ă���GameObject�̃C���X�^���X�𖼑O�Ō������A��v�������̂��ꌏ�폜����֐�
	//�������ł͍폜���X�g�Ƀv�[������邾���ŁA�폜���̂�CObjectManager�N���X��ExcuteDeleteObjects�֐��ɂčs����
	//������: LPCSTR�^ �C���X�^���X�̖��O
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->DeleteGameObject(_T("�C���X�^���X�̖��O"));
	//���ŏ��ɃC���X�^���X�̖��O����v�������̂��ꌏ�����폜����܂�
	//���m���ɂ��̃C���X�^���X���폜�������ꍇ�̓v���O���}�[��������ƃ��j�[�N�Ȗ��O�œo�^���Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���I�u�W�F�N�g�̍폜�͕K�����̊֐����Ăяo���čs������
	//���֐����d�����ߑ��p���Ȃ�����
	void DeleteGameObject(LPCSTR);

	//Objectmanager�N���X�ɓo�^����Ă���GameObject�̃C���X�^���X���ꌏ�폜����֐�
	//�������ł͍폜���X�g�Ƀv�[������邾���ŁA�폜���̂�CObjectManager�N���X��ExcuteDeleteObjects�֐��ɂčs����
	//������: CGameObject*�^ �폜�������I�u�W�F�N�g�̃|�C���^
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->DeleteGameObject(_T("�C���X�^���X�̖��O"));
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���I�u�W�F�N�g�̍폜�͕K�����̊֐����Ăяo���čs������
	//���֐����d�����ߑ��p���Ȃ�����
	void DeleteGameObject(CGameObject*);
	//������͑����f���[�g�B
	void DeleteGameObjectImmediate(CGameObject*);
	//�폜���X�g�ɓo�^����Ă���A�풓GameObject�ȊO���폜���X�g�ɂ��ׂăv�[������֐�
	//������: �Ȃ�
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->CleanManager();
	//���V�[���؂�ւ��̍ۂɌĂяo��
	//�����̊֐��ł͏풓�I�u�W�F�N�g�͍폜�ł��Ȃ�
	void CObjectManager::CleanManager();

	//�폜���X�g�ɓo�^����Ă���GameObject���폜����֐�
	//������: �Ȃ�
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->ExcuteDeleteObject();
	//���K�����C�����[�v�ōŌ�ɌĂяo��
	void ExcuteDeleteObjects();

	void Intialize();
	void Update();
	void Draw();
	const vector<OBJECT_DATA*>& GetObjectList(){
		return m_GameObjects;
	}
private:
	void Add(CGameObject*,LPCSTR, PRIORTY);
	vector<OBJECT_DATA*> m_GameObjects;	// GameObject*�̃��X�g
	vector<CGameObject*> m_DeleteObjects;	// �폜���X�g

	//vector�ɓo�^���ꂽ�v�f�����ׂč폜����֐�
	//���f�X�g���N�^�ɂČĂяo�����
	void DeleteAll();
};