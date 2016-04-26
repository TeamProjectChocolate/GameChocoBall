#pragma once

#include "stdafx.h"
#include "Scene.h"
#include "Assert.h"

#define SCENENAME_MAX 255

typedef struct SCENE_DATA{
	CHAR SceneName[SCENENAME_MAX + 1];
	CScene* Scene;
};

class CGameManager
{
	SINGLETON_DECL(CGameManager)
public:
	void AddScene(CScene*,LPCSTR);
	CScene* FindScene(LPCSTR);
	void Initialize();
	void Update();
	void Draw();
	void ChangeScene(LPCSTR);
	inline void SetNextScene(LPCSTR SceneName){
		CH_ASSERT(strlen(SceneName) <= SCENENAME_MAX);
		strcpy(m_NextSceneName, SceneName);
	}
private:
	vector<SCENE_DATA*> m_Scenes;
	CScene* m_NowScene;
	CHAR m_NextSceneName[SCENENAME_MAX + 1];
	void Add(SCENE_DATA*);
};

