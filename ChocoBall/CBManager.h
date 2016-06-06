#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "Chocoball.h"
#include "GameObject.h"
#include "Player.h"

#define CHOCO_NUM 200		//一回に流れるチョコの数


//Chocoballを管理するクラス
class CCBManager : public CGameObject{
public:
	void Initialize();
	void Update();
	void Draw();

	//進行方向をセットします。
	void SetVector(D3DXVECTOR3 vec)
	{
		m_Vector = vec;
	}

	//最初のポジションを取得できます。
	D3DXVECTOR3 GetStartPosition()
	{
		return m_pos;
	}

	//最初のポジションをセットします。
	void SetStartPosition(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	//終点のポジションをセットします。
	void SetEndPosition(D3DXVECTOR3 Epos)
	{
		m_posG = Epos;
	}

	//終点のポジションを取得できます。
	D3DXVECTOR3 GetEndPosition()
	{
		return m_posG;
	}
	//チョコボールとの衝突判定。
	bool IsHit(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	
private:
	D3DXVECTOR3			m_pos;			//生成される場所のポジション。
	D3DXVECTOR3			m_posG;			//流れていく先(ゴール)のポジション。
	D3DXVECTOR3			m_Vector;		//チョコの進行方向。
	CChocoBall			m_Choco[CHOCO_NUM];
	float				m_interval;		//インターバール。
	float				m_timer;		//タイマー。
	int					m_numCreate;	//作成済みのチョコボールの数。
};