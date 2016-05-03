#pragma once
#include "Infomation.h"
#include "Effect.h"
#include "Assert.h"


class CGameObject
{
public:
	CGameObject(){
		m_ManagerNewFlg = false;
		m_alpha = 1.0f;
	};
	~CGameObject();
	virtual void OnDestroy(){};		// ObjectManagerクラスのDeleteGameObject関数が呼ばれたときに呼び出される関数
	virtual void SetSprite(LPD3DXSPRITE){};	// 仮想関数:継承先が2Dクラスなら継承先クラスで中身を実装
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SetUpTechnique();	// エフェクトのテクニックを変える場合は継承先でこの関数をoverrideしてください
	void SetFileName(LPCSTR Name){
		CH_ASSERT(strlen(Name) < MAX_FILENAME);
		strcpy(m_pFileName, Name);
	}
	void SetAlive(bool alive){
		m_alive = alive;
	}
	bool GetAlive(){
		return m_alive;
	}
	bool GetOriginal(){
		return m_OriginalInit;
	}
	void ActiveManagerNewFlg(){
		m_ManagerNewFlg = true;
	}
	bool GetManagerNewFlg(){
		return m_ManagerNewFlg;
	}
	void SetAlpha(float alpha){
		m_alpha = alpha;
	}
protected:
	CHAR m_pFileName[MAX_FILENAME + 1];		// 読み込むファイルの名前を格納する
	TRANSEFORM m_transform; // オブジェクトの座標、回転、大きさ情報
	bool m_alive;			// 生存フラグ(trueなら生存、falseなら死亡)
// オーバーロード初期化フラグ
// (継承先のクラスでInitialize関数のオーバーロードを使用した場合は、このフラグをそのクラス内で必ずtrueにしてください)
	bool m_OriginalInit;
	bool m_ManagerNewFlg;	// ObjectManagerクラスでnewされたものか判定する変数
	LPD3DXEFFECT m_pEffect;		// 使用するエフェクト
	float m_alpha;				// オブジェクトの透明度(デフォルトは1、透明度を指定したい場合は継承先で任意の値を設定してください)
};

