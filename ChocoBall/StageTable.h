#pragma once
#include "stdafx.h"


enum GimmickType{
	GimmickType_Chocoball,
	GimmickType_Wall,
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




// ステージ1で使用するオブジェクトの定義配列
// ※新しいステージを作ったら同じ書き方で新しい配列を追加してください
// ※オブジェクトの名前は、同じステージの中でなければ被っても構いません
static LPCSTR StageGameObject_1[] = {
	{ "BulletPhysics" },
	{ "TESTStage3D" },
	{ "2DTest" },
	{ "Number" },
	{ "Camera" },
	{ "EnemyManager" },
	{ "TEST3D" }
};

// 上に新しい配列を追加したらここにそのオブジェクト配列のポインタを順番どおりに格納してください
// ※その後、一番下にある、配列の要素数を格納する配列も更新してください

static LPCSTR* StageArray[] = {
	StageGameObject_1
};

// ステージオブジェクト配列の要素数を格納する配列
static int StageObjectNumArray[] = {
	ARRAYSIZE(StageGameObject_1)
};



// ステージ1で使用するギミックやエネミーのポジションなどを設定した配列
// ※ステージを追加したら同じような配列を新しく作って、追加したステージの出力ヘッダーを読み込んでください
static SEnemyAndGimmickInfo infoTable_1[] = {
#include "EnemyGimmickInfo.h"
};

// ステージ1で使用するギミックやエネミーのポジションなどを設定した配列のポインタを格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static SEnemyAndGimmickInfo* infoTableArray[] = {
	infoTable_1
};

// ステージ1で使用するギミックやエネミーのポジションなどを設定した配列の要素数を格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static int InfoTableSizeArray[] = {
	ARRAYSIZE(infoTable_1)
};



// ステージ1で使用するギミック発動用当たり判定
// ※ステージを追加したら同じような配列を新しく作って、追加したステージの出力ヘッダーを読み込んでください
static SCollisionInfo GimmickTriggerInfoTable_1[] = {
#include "GimmickTriggerInfo.h"
};

// ステージ1で使用するギミック発動用当たり判定を設定した配列のポインタを格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static SCollisionInfo* GimmickinfoTableArray[] = {
	GimmickTriggerInfoTable_1
};

// ステージ1で使用するギミック発動用当たり判定を設定した配列の要素数を格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static int GimmickInfoTableSizeArray[] = {
	ARRAYSIZE(GimmickTriggerInfoTable_1)
};



// ステージ1のフィールドの当たり判定
// ※ステージを追加したら同じような配列を新しく作って、追加したステージの出力ヘッダーを読み込んでください
static SCollisionInfo collisionInfoTable_1[] = {
#include "collisionInfo.h"
};

// ステージ1のフィールドの当たり判定を設定した配列のポインタを格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static SCollisionInfo* collisionInfoTableArray[] = {
	collisionInfoTable_1
};

// ステージ1でのフィールドの当たり判定を設定した配列の要素数を格納する配列
// ※ステージを追加したら下のような書き方で配列に要素を追加してください
static int collisionInfoTableSizeArray[] = {
	ARRAYSIZE(collisionInfoTable_1)
};
