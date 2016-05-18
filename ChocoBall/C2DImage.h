#pragma once
#include "GraphicsDevice.h"
#include "GameObject.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct SVertex
{
	FLOAT x, y, z, w;
	DWORD color;
	FLOAT u, v;
};

class C2DImage :public CGameObject
{
public:
	C2DImage(){
		m_pTexture = nullptr;
		m_pVertexBuffer = nullptr;
		m_Split.x = 1;
		m_Split.y = 1;
		m_Now.x = 0;
		m_Now.y = 0;
	};
	~C2DImage(){
		SAFE_RELEASE(m_pVertexBuffer);
	};
	virtual void SetImage();
	virtual void Initialize()override;
	virtual void Draw()override;
	virtual void SetUpTechnique()override{
		m_pEffect->SetTechnique("BasicTec");
	}
	void LoadTextureFile();
	void SetupMatrices();
	void SetupMatrices(RECT,D3DXVECTOR2,D3DXVECTOR2);
	void SetRotation(float rota){
		D3DXQuaternionRotationAxis(&m_transform.angle, &D3DXVECTOR3(0.0f,0.0f,1.0f), rota);
	}
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DCOLOR m_backColor;			//�w�i�J���[
	D3DXVECTOR2 m_texCenter;		//�e�N�X�`���̒��_
	RECT m_rect;					//�`���`
	D3DXIMAGE_INFO imgInfo;			//�摜���i�[�p�\����
	D3DXVECTOR2 m_Split;		// �摜������
	D3DXVECTOR2 m_Now;			// ���݉��R�}�ڂ�
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;		// �������ꂽ���_�o�b�t�@�ւ̃|�C���^���i�[����ϐ�
	D3DXMATRIX mWorld;		// ���[���h�s��
};

