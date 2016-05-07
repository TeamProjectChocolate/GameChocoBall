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
	void SetRotation(float rota){
		D3DXQuaternionRotationAxis(&m_transform.angle, &D3DXVECTOR3(0.0f,0.0f,1.0f), rota);
	}
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ
	D3DCOLOR m_backColor;			//背景カラー
	D3DXVECTOR2 m_texCenter;		//テクスチャの中点
	RECT m_rect;					//描画矩形
	D3DXIMAGE_INFO imgInfo;			//画像情報格納用構造体
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;		// 生成された頂点バッファへのポインタを格納する変数
	D3DXMATRIX mWorld;		// ワールド行列
};

