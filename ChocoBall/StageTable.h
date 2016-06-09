#pragma once
#include "stdafx.h"


enum GimmickType{
	GimmickType_Chocoball,
	GimmickType_Wall,
	GimmickType_FallFloor,
};
struct SEnemyAndGimmickInfo{
	D3DXVECTOR3 pos;
	D3DXQUATERNION rot;
	D3DXVECTOR3 scale;
	int enemyType;
	int gimmickType;
};
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;
};



// フィールドのXファイル名
// ※上から順にステージ1,2,3……
static LPCSTR FieldNameArray[] = {
	"image/SUTE2_01.x",
	"image/SUTE2_01.x"
};


// ステージ1で使用するオブジェクトの定義配列
// ※新しいステージを作ったら同じ書き方で新しい配列を追加してください
// ※オブジェクトの名前は、同じステージの中でなければ被っても構いません
// ※下の配列に新しい名前のオブジェクトを追加したらStage.cppのActivateObjects関数にif文を追加してください
static LPCSTR StageGameObject_1[] = {
	{ "BulletPhysics" },// すべてのステージにこれが必要です
	{ "TESTStage3D" },// すべてのステージにこれが必要です
	{ "Number" },// すべてのステージにこれが必要です
	{ "Camera" },// すべてのステージにこれが必要です
	{ "EnemyManager" },// すべてのステージにこれが必要です
	{ "TEST3D" },// すべてのステージにこれが必要です
	{ "2DTest" },
};
static LPCSTR StageGameObject_2[] = {
	{ "BulletPhysics" },	// すべてのステージにこれが必要です
	{ "TESTStage3D" },	// すべてのステージにこれが必要です
	{ "Number" },	// すべてのステージにこれが必要です
	{ "Camera" },	// すべてのステージにこれが必要です
	{ "EnemyManager" },	// すべてのステージにこれが必要です
	{ "TEST3D" },	// すべてのステージにこれが必要です
};

// 上に新しい配列を追加したらここにそのオブジェクト配列のポインタを順番どおりに格納してください
// ※その後、一番下にある、配列の要素数を格納する配列も更新してください

static LPCSTR* StageArray[] = {
	StageGameObject_1,
	StageGameObject_2
};

// ステージオブジェクト配列の要素数を格納する配列
static int StageObjectNumArray[] = {
	ARRAYSIZE(StageGameObject_1),
	ARRAYSIZE(StageGameObject_2)
};



// ステージごとのプレイヤーのポジション情報を格納
static SCollisionInfo PlayerTransformArray[] = {
#include "PlayerPositionInfoStage1.h"
#include "PlayerPositionInfoStage2.h"
};



// ステージ1で使用するギミックやエネミーのポジションなどを設定した配列
// ※ステージを追加したら同じような配列を新しく作って、追加したステージの出力ヘッダーを読み込んでください
static SEnemyAndGimmickInfo infoTable_1[] = {
#include "EnemyGimmickInfoStage1.h"
};
static SEnemyAndGimmickInfo infoTable_2[] = {
#include "EnemyGimmickInfoStage2.h"
};

// ステージ1で使用するギミックやエネミーのポジションなどを設定した配列のポインタを格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static SEnemyAndGimmickInfo* infoTableArray[] = {
	infoTable_1,
	infoTable_2
};

// ステージ1で使用するギミックやエネミーのポジションなどを設定した配列の要素数を格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static int InfoTableSizeArray[] = {
	ARRAYSIZE(infoTable_1),
	ARRAYSIZE(infoTable_2)
};



// ステージ1で使用するギミック発動用当たり判定
// ※ステージを追加したら同じような配列を新しく作って、追加したステージの出力ヘッダーを読み込んでください
static SCollisionInfo GimmickTriggerInfoTable_1[] = {
#include "GimmickTriggerInfoStage1.h"
};
static SCollisionInfo GimmickTriggerInfoTable_2[] = {
#include "GimmickTriggerInfoStage2.h"
};

// ステージ1で使用するギミック発動用当たり判定を設定した配列のポインタを格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static SCollisionInfo* GimmickinfoTableArray[] = {
	GimmickTriggerInfoTable_1,
	GimmickTriggerInfoTable_2
};

// ステージ1で使用するギミック発動用当たり判定を設定した配列の要素数を格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static int GimmickInfoTableSizeArray[] = {
	ARRAYSIZE(GimmickTriggerInfoTable_1),
	ARRAYSIZE(GimmickTriggerInfoTable_2)
};



// ステージ1のフィールドの当たり判定
// ※ステージを追加したら同じような配列を新しく作って、追加したステージの出力ヘッダーを読み込んでください
static SCollisionInfo collisionInfoTable_1[] = {
#include "collisionInfoStage1.h"
};
static SCollisionInfo collisionInfoTable_2[] = {
#include "collisionInfoStage2.h"
};


// ステージ1のフィールドの当たり判定を設定した配列のポインタを格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static SCollisionInfo* collisionInfoTableArray[] = {
	collisionInfoTable_1,
	collisionInfoTable_2
};

// ステージ1でのフィールドの当たり判定を設定した配列の要素数を格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static int collisionInfoTableSizeArray[] = {
	ARRAYSIZE(collisionInfoTable_1),
	ARRAYSIZE(collisionInfoTable_2)
};
