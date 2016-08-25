#pragma once
#include "Infomation.h"
#include "Effect.h"
#include "Assert.h"


class CGameObject
{
public:
	CGameObject(){
		m_pEffect = nullptr;
		m_OriginalInit = false;
		m_ManagerNewFlg = false;
		m_alpha = 1.0f;
		m_alive = false;
	};
	virtual ~CGameObject();
	virtual void OnDestroy(){};		// ObjectManagerクラスのDeleteGameObject関数が呼ばれたときに呼び出される関数
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DrawDepth(LPD3DXEFFECT,const D3DXVECTOR2&);
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
	virtual void SetPos(D3DXVECTOR3 pos){
		m_transform.position = pos;
	}
	virtual D3DXVECTOR3 GetPos()
	{
		return m_transform.position;
	}
	virtual void SetScale(const D3DXVECTOR3 scale){
		m_transform.scale = scale;
	}
	D3DXVECTOR3 GetmoveSpeed()
	{
		return m_moveSpeed;

	}
	void SetAlpha(float alpha){
		m_alpha = alpha;
	}
	float GetAlpha(){
		return m_alpha;
	}
	void SetCommon(bool common){
		m_common = common;
	}
	bool GetCommon(){
		return m_common;
	}
protected:
	CHAR m_pFileName[MAX_FILENAME + 1];		// 読み込むファイルの名前を格納する
	TRANSEFORM m_transform; // オブジェクトの座標、回転、大きさ情報
	D3DXVECTOR3 m_moveSpeed;
// オーバーロード初期化フラグ
// (継承先のクラスでInitialize関数のオーバーロードを使用した場合は、このフラグをそのクラス内で必ずtrueにしてください)
	bool m_OriginalInit;
	LPD3DXEFFECT m_pEffect;		// 使用するエフェクト
private:
	bool m_ManagerNewFlg;	// ObjectManagerクラスでnewされたものか判定する変数
	bool m_alive;			// 生存フラグ(trueなら生存、falseなら死亡)
	float m_alpha;			// オブジェクトの透明度(デフォルトは1、透明度を指定したい場合は継承先で任意の値を設定してください)
	bool m_common;			// 常駐フラグ(trueならシーン切り替えで削除されない)
};

