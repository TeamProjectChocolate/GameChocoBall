#include "stdafx.h"
#include "BuildBlock.h"

CBuildBlock::CBuildBlock(){}

void CBuildBlock::Initialize()
{

	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			D3DXVECTOR3 pos(-2.5f + j*BLOCK_W, -1.0f + i*BLOCK_H, -9.0f);
			m_blocks[i][j].Initialize(pos);
		}
	}
	//eŽqŠÖŒW‚Ì\’zB
	for (int i = 0; i < BUILD_W; i++){
		for (int j = 0; j < BUILD_H-1; j++){
			m_blocks[j+1][i].SetParent(&m_blocks[j][i]);
		}
	}
	SetAlive(true);
}

void CBuildBlock::Update()
{
	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			if (m_blocks[i][j].IsDead()){
				continue;
			}
			if (m_blocks[i][j].GetAlive()){
				m_blocks[i][j].Update();
			}
			else
			{
				m_blocks[i][j].OnDestroy();
			}
		}
	}
	if (GetAsyncKeyState('D')){
		for (int i = 0; i < BUILD_H; i++){
			for (int j = 0; j < BUILD_W; j++){
				if (!m_blocks[i][j].IsDead()){
					m_blocks[i][j].OnDestroy();
				}
			}
		}
	}
}


void CBuildBlock::Draw()
{
	for (int i = 0; i < BUILD_H; i++){

		for (int j = 0; j < BUILD_W; j++){
			if (m_blocks[i][j].GetAlive()){
				m_blocks[i][j].Draw();
			}
		}
	}
}