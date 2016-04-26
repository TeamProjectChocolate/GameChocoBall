#include "stdafx.h"
#include "GameManager.h"


CGameManager* CGameManager::m_instance = nullptr;

void CGameManager::AddScene(CScene* SceneInstance, LPCSTR SceneName){
	CH_ASSERT(strlen(SceneName) <= SCENENAME_MAX);
	if (FindScene(SceneName) != nullptr){
		MessageBox(NULL, "その名前のSceneインスタンスはすでに登録されています", 0, 0);
		return;
	}
	SCENE_DATA SceneData;
	strcpy(SceneData.SceneName, SceneName);
	SceneData.Scene = SceneInstance;
	Add(&SceneData);
}

void CGameManager::Add(SCENE_DATA* data){
	m_Scenes.push_back(data);
}

CScene* CGameManager::FindScene(LPCSTR SceneName){
	int size = m_Scenes.size();
	for (int idx = 0; idx < size; idx++){
		if (!strcmp(m_Scenes[idx]->SceneName, SceneName)){
			return m_Scenes[idx]->Scene;
		}
	}
	return nullptr;
}

void CGameManager::ChangeScene(LPCSTR SceneName){
	CH_ASSERT(strlen(SceneName) <= SCENENAME_MAX);

}

void CGameManager::Initialize(){
	m_NowScene->Initialize();
}

void CGameManager::Update(){
	m_NowScene->Update();
}

void CGameManager::Draw(){
	m_NowScene->Draw();
}
