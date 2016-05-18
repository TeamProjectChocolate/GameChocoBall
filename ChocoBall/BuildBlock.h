#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "Block.h"
#include "GameObject.h"

#define BUILD_H 3		//生成される壁の高さ
#define BUILD_W 4		//生成される壁の幅
#define BLOCK_H 1.4		//ブロックのたかさ
#define BLOCK_W 1.4		//ブロックの幅


class CBuildBlock : public CGameObject{
public:
	CBuildBlock();
	void Initialize()override;
	void Update()override;
	void Draw()override;

private:
	CBlock			m_block[BUILD_H][BUILD_W];	//壁の配列
};