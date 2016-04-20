#pragma once
#include "stdafx.h"
#include "GameObject.h"

#define MAX_PRIORTY 255


class CObjectManager
{
	SINGLETON_DECL(CObjectManager)
public:

	//�w�肵���I�u�W�F�N�g��������������֐�(�D��x���w�肵�����ꍇ)
	//������: LPCSTR�^ �C���X�^���X�̖��O 
	//		  short�^ �X�V�D��x(0���ŏ��A�������傫���قǗD��x���Ⴂ)
	//�Ԃ�l: T*�^ ���������N���X�̃I�u�W�F�N�g��ԋp
	//�Ăяo����: SINSTANCE(CObjectManager)->GenerationObject<�����������N���X��>(_T("�C���X�^���X�̖��O"),0);
	//���I�u�W�F�N�g�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���K��CObjectManager�N���X�̍폜�֐�(���O����)���Ăяo���čs������
	template<class T>
	T* GenerationObject(LPCSTR ObjectName,short priorty){
		T* Object = new T;
		if (priorty > MAX_PRIORTY){
			priorty = MAX_PRIORTY;
		}
		this->Add(Object, ObjectName,priorty);
		return Object;
	}

	//�w�肵���I�u�W�F�N�g��������������֐�(�D��x�Ȃ��F�����I�ɗD��x�͍Œ�ɂȂ�܂�)
	//������: LPCSTR�^ �C���X�^���X�̖��O
	//�Ԃ�l: T*�^ ���������N���X�̃I�u�W�F�N�g��ԋp
	//�Ăяo����: SINSTANCE(CObjectManager)->GenerationObject<�����������N���X��>(_T("�C���X�^���X�̖��O"));
	//���I�u�W�F�N�g�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���K��CObjectManager�N���X�̍폜�֐�(���O����)���Ăяo���čs������
	 template<class T>
	T* GenerationObject(LPCSTR ObjectName){
		T* Object = new T;
		short priorty = MAX_PRIORTY;
		this->Add(Object,ObjectName ,priorty);
		return Object;
	}

	//���łɐ�������Ă���I�u�W�F�N�g���}�l�[�W���[�N���X�ɓo�^����֐�(�D��x���w�肵�����ꍇ)
	//������: CGameObject*�^ �o�^����GameObject�̃|�C���^
	//		�@short�^ �X�V�D��x(0���ŏ��A�������傫���قǗD��x���Ⴂ)
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->AddObject(�ǉ��������C���X�^���X�̃|�C���^,_T("�C���X�^���X�̖��O"),0);
	//���I�u�W�F�N�g�̖��O�̓C���X�^���X���Ƃɔ��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���K��CObjectManager�N���X�̍폜�֐�(���O����)���Ăяo���čs������
	void AddObject(CGameObject*,LPCSTR, short);

	//���łɐ�������Ă���I�u�W�F�N�g���}�l�[�W���[�N���X�ɓo�^����֐�(�D��x�Ȃ��F�����I�ɗD��x�͍Œ�ɂȂ�܂�)
	//������: CGameObject*�^ �o�^����GameObject�̃|�C���^
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->AddObject(�ǉ��������C���X�^���X�̃|�C���^,_T("�C���X�^���X�̖��O"));
	//���C���X�^���X�̖��O�͔��Ȃ��悤�Ƀ��j�[�N�Ȃ��̂��v���O���}�[���w�肵�Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���K��CObjectManager�N���X�̍폜�֐�(���O����)���Ăяo���čs������
	void AddObject(CGameObject*,LPCSTR);

	//Objectmanager�N���X�ɓo�^����Ă���GameObject�̃C���X�^���X�𖼑O�Ō�������֐�
	//������: LPCSTR�^ �C���X�^���X�̖��O
	//�Ԃ�l: CGameObject*�^ �������̖��O�ƈ�v�����I�u�W�F�N�g�̃|�C���^(�ǂꂩ���)
	//�Ăяo����: SINSTANCE(CObjectManager)->FindGameObject<�����������N���X��>(_T("�C���X�^���X�̖��O"));
	//���������O����v�����ꍇ�ǂꂩ����Ԃ���܂�
	//���m���ɂ��̃C���X�^���X���擾�������ꍇ�̓v���O���}�[��������ƃ��j�[�N�Ȗ��O�œo�^���Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���K��CObjectManager�N���X�̍폜�֐�(���O����)���Ăяo���čs������
	//���֐����d�����ߑ��p���Ȃ�����
	template<class T>
	T* FindGameObject(LPCSTR ObjectName)
	{
		int size = m_GameObjects.size();
		for (int idx = 0; idx < size; idx++){
			if (!strcmp(m_GameObjects[idx]->objectname,ObjectName)){
				return (T*)m_GameObjects[idx]->object;
			}
		}
		MessageBox(NULL, "�I�u�W�F�N�g���o�^����Ă��܂���", 0, 0);
		return nullptr;
	}

	//Objectmanager�N���X�ɓo�^����Ă���GameObject�̃C���X�^���X�𖼑O�Ō������A��v�������̂��ꌏ�폜����֐�
	//������: LPCSTR�^ �C���X�^���X�̖��O
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CObjectManager)->DeleteGameObject(_T("�C���X�^���X�̖��O"));
	//���ŏ��ɃC���X�^���X�̖��O����v�������̂��ꌏ�����폜����܂�
	//���m���ɂ��̃C���X�^���X���폜�������ꍇ�̓v���O���}�[��������ƃ��j�[�N�Ȗ��O�œo�^���Ă�������
	//���I�u�W�F�N�g�̃C���X�^���X��CObjectManager�N���X�̊O����delete���Ȃ�����
	//���I�u�W�F�N�g�̍폜�͕K�����̊֐����Ăяo���čs������
	//���֐����d�����ߑ��p���Ȃ�����
	void DeleteGameObject(LPCSTR);

	void Intialize(LPD3DXSPRITE);
	void Update();
	void Draw();
private:
	void Add(CGameObject*,LPCSTR, short);
	vector<OBJECT_DATA*> m_GameObjects;
};