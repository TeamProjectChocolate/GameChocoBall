#pragma once
#include "C2DImage.h"
#include "stdafx.h"

#define NUMBER_NUM 10

typedef struct _TEXTURE
{
	string textureName;				//テクスチャ名
	LPDIRECT3DTEXTURE9 pTexture;	//テクスチャ
	D3DXIMAGE_INFO imgInfo;			//テクスチャ情報
	D3DXVECTOR2 center;				//テクスチャセンター
	short separateNum;				//テクスチャのセパレート数
	D3DCOLOR blendColor;			//ブレンドカラー
}TEXTURE;

class CNumber :public C2DImage{
public:
	void Initialize()override;
	void Update()override;
	void Draw(LPD3DXSPRITE)override;
	void SetValue(const int value){ m_value = value; };		// 外部から受け取った値をm_valueに格納
	void AddValue(const int value){ m_value += value; };		// 外部から受け取った値をm_valueに加算
	void SetPos(short x, short y){ m_position.x = x; m_position.y = y; };
private:
	int m_value;	// 数値
};