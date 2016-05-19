#include "stdafx.h"
#include "BuildBlock.h"

CBuildBlock::CBuildBlock(){}

void CBuildBlock::Initialize()
{
	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			D3DXVECTOR3 pos(-2.5f + j*BLOCK_W, -1.0f + i*BLOCK_H, -9.0f);

			m_block[i][j].Initialize(pos);
			//CGameObject::SetPos(pos);
		}
	}
	//eŽqŠÖŒW‚Ì\’zB
	for (int i = 0; i < BUILD_W; i++){
		for (int j = 0; j < BUILD_H-1; j++){
			m_block[j+1][i].SetParent(&m_block[j][i]);
		}
	}
	SetAlive(true);
}

void CBuildBlock::Update()
{
	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			if (m_block[i][j].IsDead()){
				continue;
			}
			if (m_block[i][j].GetLife()){
				m_block[i][j].Update();
			}
			else
			{
				m_block[i][j].OnDestroy();
			}
		}
	}
	if (GetAsyncKeyState('D')){
		m_block[0][1].SetLife(false);
	}
}


void CBuildBlock::Draw()
{
	for (int i = 0; i < BUILD_H; i++){

		for (int j = 0; j < BUILD_W; j++){
			if (m_block[i][j].GetLife() == true){
				m_block[i][j].Draw();
			}
		}
	}
}