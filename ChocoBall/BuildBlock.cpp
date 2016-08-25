#include "stdafx.h"
#include "BuildBlock.h"
#include "ShadowRender.h"

CBuildBlock::CBuildBlock(){}



void CBuildBlock::Initialize(D3DVECTOR pos, D3DXQUATERNION rot)
{

	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			D3DXVECTOR4 offset(j*BLOCK_W, 0.0f, 0.0f, 1.0f);
			D3DXMATRIX mRot;
			D3DXMatrixRotationQuaternion(&mRot, &rot);
			D3DXVec4Transform(&offset, &offset, &mRot);
			D3DXVECTOR3 _pos;
			_pos.x = pos.x + offset.x;
			_pos.y = pos.y + offset.y + i*BLOCK_H;
			_pos.z = pos.z + offset.z;

			m_blocks[i][j].Initialize(_pos, rot);
			//SINSTANCE(CShadowRender)->Entry(&m_blocks[i][j]);
		}
	}
	//�e�q�֌W�̍\�z�B
	for (int i = 0; i < BUILD_W; i++){
		for (int j = 0; j < BUILD_H - 1; j++){
			m_blocks[j + 1][i].SetParent(&m_blocks[j][i]);
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
	//if (GetAsyncKeyState('D')){
	//	for (int i = 0; i < BUILD_H; i++){
	//		for (int j = 0; j < BUILD_W; j++){
	//			if (!m_blocks[i][j].IsDead()){
	//				m_blocks[i][j].OnDestroy();
	//			}
	//		}
	//	}
	//}
}


void CBuildBlock::Draw()
{
	bool isBeginDraw = false;
	int beginDrawBlockNo_w = 0;
	int beginDrawBlockNo_h = 0;

	for (int i = 0; i < BUILD_H; i++){

		for (int j = 0; j < BUILD_W; j++){
			if (m_blocks[i][j].GetAlive()){
				if (!isBeginDraw){
					m_blocks[i][j].BeginDraw();
					isBeginDraw = true;
					beginDrawBlockNo_w = j;
					beginDrawBlockNo_h = i;

				}
				m_blocks[i][j].Draw();
			}
		}
	}
	if (isBeginDraw){
		m_blocks[beginDrawBlockNo_h][beginDrawBlockNo_w].EndDraw();
	}
}

void CBuildBlock::DrawDepth(LPD3DXEFFECT effect,const D3DXVECTOR2& FarNear){
	for (int i = 0; i < BUILD_H; i++){
		for (int j = 0; j < BUILD_W; j++){
			if (m_blocks[i][j].GetAlive()){
				m_blocks[i][j].DrawDepth(effect,FarNear);
			}
		}
	}
}