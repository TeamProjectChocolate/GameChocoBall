#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "Block.h"
#include "GameObject.h"

#define BUILD_H 5
//生成される壁の高さ
#define BUILD_W 6		//生成される壁の幅
#define BLOCK_H 1.0		//ブロックのたかさ
#define BLOCK_W 1.0		//ブロックの幅


class CBuildBlock : public CGameObject{
public:
	CBuildBlock();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	CBlock* GetBlocks(int x,int y){
		return &m_blocks[y][x];
	}
	int GetNum_Y(){
		return BUILD_H;
	}
	int GetNum_X(){
		return BUILD_W;
	}
private:
	CBlock			m_blocks[BUILD_H][BUILD_W];	//壁の配列
};