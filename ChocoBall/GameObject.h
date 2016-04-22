#pragma once
#include "Infomation.h"

class CGameObject
{
public:
	CGameObject(){ m_ManagerNewFlg = false; };
	~CGameObject();
	virtual void OnDestroy(){};		// ObjectManagerクラスのDeleteGameObject関数が呼ばれたときに呼び出される関数
	virtual void SetSprite(LPD3DXSPRITE){};	// 仮想関数:継承先が2Dクラスなら継承先クラスで中身を実装
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void SetAlive(bool alive){
		m_alive = alive;
	}
	bool GetAlive(){
		return m_alive;
	}
	short GetType(){
		return m_ObjecType;
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
protected:
	LPCSTR m_pFileName;		// 読み込むファイルの名前を格納する
	TRANSEFORM m_transform; // オブジェクトの座標、回転、大きさ情報
	bool m_alive;			// 生存フラグ(trueなら生存、falseなら死亡)
	short m_ObjecType;		// オブジェクトが2Dか3Dかを示す変数(0なら2D,1なら3D)
// オーバーロード初期化フラグ
// (継承先のクラスでInitialize関数のオーバーロードを使用した場合は、このフラグをそのクラス内で必ずtrueにしてください)
	bool m_OriginalInit;
	bool m_ManagerNewFlg;	// ObjectManagerクラスでnewされたものか判定する変数
};

