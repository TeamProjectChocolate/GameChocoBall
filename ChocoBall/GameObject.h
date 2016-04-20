#pragma once
#include "Infomation.h"

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
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
protected:
	LPCSTR m_pFileName;		// 読み込むファイルの名前を格納する
	TRANSEFORM m_transform; // オブジェクトの座標、回転、大きさ情報
	bool m_alive;			// 生存フラグ(trueなら生存、falseなら死亡)
	short m_ObjecType;		// オブジェクトが2Dか3Dかを示す変数(0なら2D,1なら3D)
// オーバーロード初期化フラグ
// (継承先のクラスでInitialize関数のオーバーロードを使用した場合は、このフラグをtrueにしてください)
	bool m_OriginalInit;
};

