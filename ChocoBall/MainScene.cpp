#include "stdafx.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "Audio.h"
#include "TestObject2D.h"
#include "Field.h"
#include "ShadowRender.h"
#include "Debri.h"
#include "Block.h"
#include "BuildBlock.h"
#include "Result.h"
#include "ClearText.h"
#include "GameOver.h"
#include "Number.h"
#include "EnemyManager.h"
#include "CBManager.h"
#include "StageManager.h"
#include "Score.h"


CMainScene::CMainScene(){
}

CMainScene::~CMainScene(){
}

void CMainScene::Initialize(){
	srand((unsigned int)time(NULL));
	SINSTANCE(CStageManager)->Initialize();
}

void CMainScene::Update(){
	SINSTANCE(CStageManager)->Update();
}

void CMainScene::Draw(){
	SINSTANCE(CStageManager)->Draw();
}
