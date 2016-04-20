#pragma once
#include "C2DImage.h"
#include "stdafx.h"

#define NUMBER_NUM 10

typedef struct _TEXTURE
{
	string textureName;				//�e�N�X�`����
	LPDIRECT3DTEXTURE9 pTexture;	//�e�N�X�`��
	D3DXIMAGE_INFO imgInfo;			//�e�N�X�`�����
	D3DXVECTOR2 center;				//�e�N�X�`���Z���^�[
	short separateNum;				//�e�N�X�`���̃Z�p���[�g��
	D3DCOLOR blendColor;			//�u�����h�J���[
}TEXTURE;

class CNumber :public C2DImage{
public:
	void Initialize()override;
	void Update()override;
	void Draw(LPD3DXSPRITE)override;
	void SetValue(const int value){ m_value = value; };		// �O������󂯎�����l��m_value�Ɋi�[
	void AddValue(const int value){ m_value += value; };		// �O������󂯎�����l��m_value�ɉ��Z
	void SetPos(short x, short y){ m_position.x = x; m_position.y = y; };
private:
	int m_value;	// ���l
};