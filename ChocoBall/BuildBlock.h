#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "Block.h"
#include "GameObject.h"

#define BUILD_H 4		//���������ǂ̍���
#define BUILD_W 6		//���������ǂ̕�
#define BLOCK_H 1.0		//�u���b�N�̂�����
#define BLOCK_W 1.0		//�u���b�N�̕�


class CBuildBlock : public CGameObject{
public:
	CBuildBlock();
	void Initialize()override;
	void Update()override;
	void Draw()override;

private:
	CBlock			m_block[BUILD_H][BUILD_W];	//�ǂ̔z��
};