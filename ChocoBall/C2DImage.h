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
	LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ
	D3DCOLOR m_backColor;			//背景カラー
	D3DXVECTOR2 m_texCenter;		//テクスチャの中点
	RECT m_rect;					//描画矩形
	D3DXIMAGE_INFO imgInfo;			//画像情報格納用構造体
	//LPD3DXSPRITE m_pSprite;			//渡されたスプライトを格納
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;		// 生成された頂点バッファへのポインタを格納する変数
	D3DXMATRIX mWorld;		// ワールド行列
};

