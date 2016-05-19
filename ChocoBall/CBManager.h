#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "Chocoball.h"
#include "GameObject.h"

#define CHOCO_NUM 3		//一回に流れるチョコの数


//Chocoballを管理するクラス
class CCBManager : public CGameObject{
public:
	void Initialize();
	void Update();
	void Draw();

	void SetVector(D3DXVECTOR3 vec)
	{
		m_Vector = vec;
	}

	D3DXVECTOR3 GetPosition()
	{
		return m_pos;
	}
	void SetPosition(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

private:
	D3DXVECTOR3			m_pos;
	D3DXVECTOR3			m_Vector;		//チョコの進行方向
	CChocoBall			m_Choco[CHOCO_NUM];
};