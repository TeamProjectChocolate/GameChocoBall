#pragma once
#include "stdafx.h"
#include "C3DImage.h"

class Bullet : public C3DImage
{
public:
	Bullet();
	~Bullet();
	void Initialize()override{};
	void Update()override{};
	void Draw()override{};
	void SetUpTechnique()override{}
private:
	D3DXVECTOR3 m_position;				//�e�̍��W
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
};

