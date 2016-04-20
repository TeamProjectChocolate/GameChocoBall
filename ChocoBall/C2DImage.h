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
	D3DXVECTOR2 m_position;			//位置情報
	float m_angle;					//回転情報
	D3DXVECTOR2 m_scale;			//スケール情報
	LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ
	D3DCOLOR m_backColor;			//背景カラー
	D3DXVECTOR2 m_texCenter;		//テクスチャの中点
	RECT m_rect;					//描画矩形
	D3DXMATRIX m_transformMatrix;	//変換行列
	D3DXIMAGE_INFO imgInfo;			//画像情報格納用構造体
	LPD3DXSPRITE m_pSprite;			//渡されたスプライトを格納
};

