#include "stdafx.h"
#include "BuildBlock.h"
#include "ShadowRender.h"


CBuildBlock::CBuildBlock(){}


void CBuildBlock::Initialize()
{
	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			D3DXVECTOR3 pos(-1.5f + j*BLOCK_W, -1.0f + i*BLOCK_H, -5.0f);
			m_block[i][j].Initialize(pos);
			CGameObject::SetPos(pos);
		}
	}
	SetAlive(true);
}

void CBuildBlock::Update()
{
	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			m_block[i][j].Update();
		}
	}
}

void CBuildBlock::Draw()
{
	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			m_block[i][j].Draw();
		}
	}
}
