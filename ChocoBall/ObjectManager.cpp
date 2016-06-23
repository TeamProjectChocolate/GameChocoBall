#include "stdafx.h"
#include "ObjectManager.h"
#include "C2DImage.h"
#include "Player.h"
#include "RenderContext.h"

CObjectManager* CObjectManager::m_instance = nullptr;

void CObjectManager::AddObject(CGameObject* Object, LPCSTR ObjectName, PRIORTY priorty,bool common){
	if (priorty > PRIORTY::LOWEST){
		priorty = PRIORTY::LOWEST;
	}
	Object->SetCommon(common);
	this->Add(Object,ObjectName,priorty);
}

void CObjectManager::AddObject(CGameObject* Object,LPCSTR ObjectName,bool common){
	PRIORTY priorty = PRIORTY::LOWEST;
	Object->SetCommon(common);
	this->Add(Object,ObjectName, priorty);
}

void CObjectManager::Add(CGameObject* GameObject,LPCSTR ObjectName, PRIORTY priority){
	OBJECT_DATA* Obj;
	Obj = new OBJECT_DATA;
	CH_ASSERT(strlen(ObjectName) < OBJECTNAME_MAX);
	strcpy(Obj->objectname, ObjectName);		// �R�s�[�����ɃA�h���X��ێ�������ƁA���[�J���ϐ����n���ꂽ�ۂɃN���b�V������
	Obj->object = GameObject;
	Obj->priority = priority;
	m_GameObjects.push_back(Obj);
}

void CObjectManager::DeleteGameObject(LPCSTR ObjectName){
	int size = m_GameObjects.size();
	for (int idx = 0; idx < size; idx++){
		if (!strcmp(m_GameObjects[idx]->objectname, ObjectName)){
			m_GameObjects[idx]->object->OnDestroy();
			m_DeleteObjects.push_back(m_GameObjects[idx]->object);
			return;
		}
	}
	MessageBox(NULL, "�I�u�W�F�N�g���o�^����Ă��܂���", 0, 0);
}

void CObjectManager::DeleteGameObject(CGameObject* pObject){
	int size = m_GameObjects.size();
	m_DeleteObjects.push_back(pObject);
}

void CObjectManager::DeleteGameObjectImmediate(CGameObject* pObject)
{
	pObject->OnDestroy();
	vector<OBJECT_DATA*>::iterator itr;
	for (itr = m_GameObjects.begin(); itr != m_GameObjects.end(); itr++){
		if (!(*itr)->object->GetManagerNewFlg()){
			if (pObject == (*itr)->object){
				m_GameObjects.erase(itr);
				break;
			}
		}
	}
}
void CObjectManager::CleanManager(){
	int size = m_GameObjects.size();
	for (int idx = 0; idx < size; idx++){
		if (!m_GameObjects[idx]->object->GetCommon()){
			m_GameObjects[idx]->object->OnDestroy();
			m_DeleteObjects.push_back(m_GameObjects[idx]->object);
		}
	}
}

void CObjectManager::ExcuteDeleteObjects(){
	vector<OBJECT_DATA*>::iterator itr;
	int size = m_DeleteObjects.size();
	for (int idx = 0; idx < size; idx++){
		for (itr = m_GameObjects.begin(); itr != m_GameObjects.end();){
			if (m_DeleteObjects[idx] == (*itr)->object){
				if ((*itr)->object->GetManagerNewFlg()){
					SAFE_DELETE((*itr)->object);
					SAFE_DELETE((*itr));
				}
				itr = m_GameObjects.erase(itr);	
				break;
			}
			else{
				itr++;
			}
		}
	}
	m_DeleteObjects.clear();
}

void CObjectManager::Intialize(){
	int size = m_GameObjects.size();
	for (int priorty = 0; priorty <= MAX_PRIORTY; priorty++){
		for (int idx = 0; idx < size; idx++){
			if (m_GameObjects[idx]->priority == priorty){
				if (!(m_GameObjects[idx]->object->GetOriginal())){
					m_GameObjects[idx]->object->Initialize();
				}
			}
		}
	}
}

void CObjectManager::Update(){
	int size = m_GameObjects.size();
	for (short priorty = 0; priorty <= MAX_PRIORTY;priorty++){	// �D��x�̍������̂���X�V
		for (int idx = 0; idx < size; idx++){
			if (m_GameObjects[idx]->object->GetAlive()){	// �������Ă�����̂̂ݍX�V
				if (m_GameObjects[idx]->priority == priorty){	// ���݂̗D��x�ƈ�v������̂��X�V
					m_GameObjects[idx]->object->Update();
				}
			}
		}
	}
}

void CObjectManager::Draw(){
	SINSTANCE(CRenderContext)->RenderingStart();
	int size = m_GameObjects.size();
	for (short priorty = 0; priorty <= MAX_PRIORTY; priorty++){	// �D��x�̍������̂���X�V
		if (priorty == PRIORTY::OBJECT2D){
			// 3D�`�悪�I������烌���_�����O�^�[�Q�b�g�����ɖ߂�
			SINSTANCE(CRenderContext)->RenderingEnd();
			SINSTANCE(CRenderContext)->SetRenderingBuffer();
		}
		for (int idx = 0; idx < size; idx++){
			if (m_GameObjects[idx]->object->GetAlive()){	// �������Ă�����̂̂ݕ`��
				if (m_GameObjects[idx]->priority == priorty){	// ���݂̗D��x�ƈ�v������̂�`��
					m_GameObjects[idx]->object->Draw();
				}
			}
		}
	}
}

void CObjectManager::DeleteAll(){
	for (int idx = 0, size = m_GameObjects.size(); idx < size; idx++){
		SAFE_DELETE(m_GameObjects[idx]->object);
		SAFE_DELETE(m_GameObjects[idx]);
	}
	m_GameObjects.clear();
}