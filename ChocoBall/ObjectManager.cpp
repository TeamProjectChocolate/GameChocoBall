#include "stdafx.h"
#include "ObjectManager.h"
#include "C2DImage.h"

CObjectManager* CObjectManager::m_instance = nullptr;

void CObjectManager::AddObject(CGameObject* Object, LPCSTR ObjectName, short priorty){
	if (priorty > MAX_PRIORTY){
		priorty = MAX_PRIORTY;
	}
	this->Add(Object,ObjectName,priorty);
}

void CObjectManager::AddObject(CGameObject* Object,LPCSTR ObjectName){
	short priorty = MAX_PRIORTY;
	this->Add(Object,ObjectName, priorty);
}

void CObjectManager::Add(CGameObject* GameObject,LPCSTR ObjectName, short priority){
	OBJECT_DATA* Obj;
	Obj = new OBJECT_DATA;
	Obj->objectname = ObjectName;
	Obj->object = GameObject;
	Obj->priority = priority;
	m_GameObjects.push_back(Obj);
}

void CObjectManager::DeleteGameObject(LPCSTR ObjectName){
	int size = m_GameObjects.size();
	vector<OBJECT_DATA*>::iterator itr = m_GameObjects.begin();
	for (itr; itr != m_GameObjects.end();){
		if (!strcmp((*itr)->objectname, ObjectName)){
			SAFE_DELETE((*itr)->object);
			SAFE_DELETE((*itr));
			itr = m_GameObjects.erase(itr);
			return;
		}
		else{
			itr++;
		}
	}
	MessageBox(NULL, "オブジェクトが登録されていません", 0, 0);
}

void CObjectManager::Intialize(LPD3DXSPRITE pSprite){
	int size = m_GameObjects.size();
	for (int idx = 0; idx < size; idx++){
		if (!(m_GameObjects[idx]->object->GetOriginal())){
			if (m_GameObjects[idx]->object->GetType() == OBJECT::TYPE_3D){
				m_GameObjects[idx]->object->Initialize();
			}
			else{
				m_GameObjects[idx]->object->SetSprite(pSprite);
				m_GameObjects[idx]->object->Initialize();
			}
		}
	}
}

void CObjectManager::Update(){
	int size = m_GameObjects.size();
	for (short priorty = 0; priorty <= MAX_PRIORTY;priorty++){	// 優先度の高いものから更新
		for (int idx = 0; idx < size; idx++){
			if (m_GameObjects[idx]->object->GetAlive()){	// 生存しているもののみ更新
				if (m_GameObjects[idx]->priority == priorty){
					m_GameObjects[idx]->object->Update();
				}
			}
		}
	}
}

void CObjectManager::Draw(){
	int size = m_GameObjects.size();
	for (int idx = 0; idx < size; idx++){
		if (m_GameObjects[idx]->object->GetAlive()){	// 生存しているもののみ描画
			m_GameObjects[idx]->object->Draw();
		}
	}
}
