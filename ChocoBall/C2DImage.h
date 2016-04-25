#pragma once
#include "GraphicsDevice.h"
#include "GameObject.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

struct SVertex
{
	FLOAT x, y, z, w;
	DWORD color;
	FLOAT u, v;

	//D3DXVECTOR4 pos;
	//DWORD color;
	//FLOAT u,v;
};

class C2DImage :public CGameObject
{
public:
	C2DImage(){};
	~C2DImage(){};
	virtual void SetImage();
	virtual void Initialize()override;
	virtual void Draw()override;
	virtual void SetUpTechnique()override{
		m_pEffect->SetTechnique("BasicTec");
	}
	void LoadTextureFile();
	void SetupMatrices();
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DCOLOR m_backColor;			//�w�i�J���[
	D3DXVECTOR2 m_texCenter;		//�e�N�X�`���̒��_
	RECT m_rect;					//�`���`
	D3DXIMAGE_INFO imgInfo;			//�摜���i�[�p�\����
	//LPD3DXSPRITE m_pSprite;			//�n���ꂽ�X�v���C�g���i�[
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;		// �������ꂽ���_�o�b�t�@�ւ̃|�C���^���i�[����ϐ�
	D3DXMATRIX mWorld;		// ���[���h�s��
};

