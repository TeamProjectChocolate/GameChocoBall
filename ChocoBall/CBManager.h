#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "Chocoball.h"
#include "GameObject.h"
#include "Player.h"
#include "CourceDef.h"
#include "ShadowRender.h"


#define CHOCO_NUM 200	//一回に流れるチョコの数

struct SInstancingVertex{
	FLOAT x, y, z, w;
	DWORD color;
	FLOAT u, v;
	int Index;
public:
	void SetIndex(const int& index){
		this->Index = index;
	}
};
//Chocoballを管理するクラス
class CCBManager : public CGameObject{
public:
	CCBManager(){};
	~CCBManager(){
		for (int idx = 0; idx <= CHOCO_NUM; idx++){
			SINSTANCE(CShadowRender)->DeleteObjectImidieit(&m_Choco[idx]);
		}
	};
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void DrawDepth(LPD3DXEFFECT,const D3DXVECTOR2&)override;
	void FindCource();
	void NonActivate();

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
	
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
	int GetCourceNo(){
		return m_InitPosOfCourceNo;
	}
private:
	D3DXVECTOR3			m_pos;			//生成される場所のポジション。
	D3DXVECTOR3			m_posG;			//流れていく先(ゴール)のポジション。
	D3DXVECTOR3			m_Vector;		//チョコの進行方向。
	CChocoBall			m_Choco[CHOCO_NUM];
	float				m_interval;		//インターバル。
	float				m_timer;		//タイマー。
	int					m_numCreate;	//作成済みのチョコボールの数。
	int					m_InitPosOfCourceNo;// チョコボールが生成された場所のコースナンバー
	CCourceDef m_CourceDef;
	STAGE_ID m_StageID;
	bool m_IsFirst;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
};