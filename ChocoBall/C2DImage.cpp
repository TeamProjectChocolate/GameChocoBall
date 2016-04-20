#include "stdafx.h"
#include "C2DImage.h"
#include "GraphicsDevice.h"
#include "ImageManager.h"


void C2DImage::Initialize()
{
	IMAGE2D* Image = SINSTANCE(CImageManager)->Find2DImage(m_pFileName);
	if (Image != nullptr){
		m_pTexture = Image->pTex;
		m_rect = Image->rect;
		m_texCenter = D3DXVECTOR2(m_rect.right / 2, m_rect.bottom / 2);
		return;
	}
	LoadTextureFile();
}

void C2DImage::LoadTextureFile(){
	D3DXIMAGE_INFO imgInfo;										//画像情報格納用構造体
	D3DXCreateTextureFromFileEx(graphicsDevice(), this->m_pFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0xff000000, &imgInfo, NULL, &this->m_pTexture);	//テクスチャ読込
	this->m_texCenter = D3DXVECTOR2((float)imgInfo.Width / 2, (float)imgInfo.Height / 2);	//テクスチャの中点セット
	RECT rec = { 0, 0, imgInfo.Width, imgInfo.Height };			//描画領域
	memcpy(&this->m_rect, &rec, sizeof(RECT));					//描画領域セット
	SINSTANCE(CImageManager)->Add2D(m_pFileName, m_pTexture, m_rect);
}

void C2DImage::Draw()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);		//スプライト描画開始
	m_pSprite->SetTransform(&this->m_transformMatrix);	//変換行列セット
	m_pSprite->Draw(this->m_pTexture, &this->m_rect, &D3DXVECTOR3(this->m_texCenter.x, this->m_texCenter.y, 0.0f), NULL, this->m_backColor);	//スプライトにテクスチャ貼付け
	m_pSprite->End();	//スプライト描画終了
}

void C2DImage::SetupMatrices()
{
	D3DXMatrixIdentity(&this->m_transformMatrix);	//ワールド行列初期化
	D3DXMatrixTransformation2D(&this->m_transformMatrix, NULL, 0.0f, &this->m_scale, NULL, D3DXToRadian(this->m_angle), &this->m_position);	//変換行列作成
}