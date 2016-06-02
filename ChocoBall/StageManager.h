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

	//次のステージへ移行する関数
	void SetNextStage();

	//ステージ切り替え関数
	//引き数: LPCSTR型 どのステージに切り替えるか
	//返り値: なし
	//呼び出し例: SINSTANCE(CStageManager)->ChangeStage(_T("インスタンスの名前"));
	//※関数が重いため多用しないこと
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
	bool m_IsContinue;		// ステージを続きから遊ぶ場合はtrue,そうでなければfalse
	STAGE_ID m_ContinueStage;	// ゲームオーバーしたときに現在のステージを保持する
	STAGE_ID m_NowStage;
	STAGE_ID m_NextStage;

	CStage m_Stage;

	CAudio* m_pAudio;
	//※デストラクタにて呼び出される
	void DeleteAll();
};

// ステージ1で使用するオブジェクトの登録情報格納用構造体配列
static GENERATION_OBJECT_DATA StageGameObject_1[] = {
	{ "TESTStage3D", PRIORTY::OBJECT3D, false, GENERATION_OBJECT_DATA::GenerationObject<CField>() },
	{ "2DTest", PRIORTY::OBJECT2D_ALPHA, false, GENERATION_OBJECT_DATA::GenerationObject<CTestObject2D>() },
	{ "Number", PRIORTY::OBJECT2D_ALPHA,false,GENERATION_OBJECT_DATA::GenerationObject<CNumber>()},
	{ "Camera" ,PRIORTY::CONFIG,true,GENERATION_OBJECT_DATA::GenerationObject<CCourceCamera>()},
	{ "EnemyManager" ,PRIORTY::PLAYER,false,GENERATION_OBJECT_DATA::GenerationObject<CEnemyManager>()},
	{ "TEST3D", PRIORTY::PLAYER, false, GENERATION_OBJECT_DATA::GenerationObject<CPlayer>() }
};


// ステージを追加したらここにステージで使用するオブジェクト配列のポインタをステージの順番どおりに格納してください
static GENERATION_OBJECT_DATA* StageArray[] = {
	StageGameObject_1
};

static int StageObjectNumArray[] = {
	ARRAYSIZE(StageGameObject_1)
};
