#pragma once
#include "GraphicsDevice.h"
#include "GameObject.h"

class C2DImage :public CGameObject
{
public:
	C2DImage(){ m_ObjecType = OBJECT::TYPE_2D; };
	~C2DImage(){};
	void SetSprite(LPD3DXSPRITE pSprite)override{
		m_pSprite = pSprite;
	}
	virtual void Initialize()override;
	virtual void Draw()override;
	void LoadTextureFile();
	void SetupMatrices();
protected:
	D3DXVECTOR2 m_position;			//�ʒu���
	float m_angle;					//��]���
	D3DXVECTOR2 m_scale;			//�X�P�[�����
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DCOLOR m_backColor;			//�w�i�J���[
	D3DXVECTOR2 m_texCenter;		//�e�N�X�`���̒��_
	RECT m_rect;					//�`���`
	D3DXMATRIX m_transformMatrix;	//�ϊ��s��
	D3DXIMAGE_INFO imgInfo;			//�摜���i�[�p�\����
	LPD3DXSPRITE m_pSprite;			//�n���ꂽ�X�v���C�g���i�[
};

