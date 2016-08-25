#pragma once

#include "stdafx.h"
#include "Light.h"
#include "Primitive.h"
#include "BloomRender.h"
#include "DofRender.h"

class CCamera;

class CRenderContext{
	SINGLETON_DECL(CRenderContext)
public:
	void CreateRenderingTerget();
	void RenderingStart();
	void RenderingEnd();
	void SetRenderingBuffer();

	void SetCurrentCamera(CCamera* cam)
	{
		m_pCamera = cam;
	}
	CCamera* GetCurrentCamera()
	{
		return m_pCamera;
	}
	void SetCurrentLight(CLight* light){
		m_pLight = light;
	}
	CLight* GetCurrentLight(){
		return m_pLight;
	}
	LPDIRECT3DSURFACE9 GetRenderingTarget(){
		return m_pOriginalSurf;
	}
	LPDIRECT3DSURFACE9 GetMapZ(){
		return m_pMapZ;
	}
	LPDIRECT3DTEXTURE9 GetTexture(){
		return m_pTexture;
	}
	unsigned int GetWindowWidth(){
		return  m_bufferSize_Width;
	}
	unsigned int GetWindowHeight(){
		return  m_bufferSize_Height;
	}
	CPrimitive* GetPrimitive(){
		return &m_copyBackBufferPrim;
	}
	CDofRender* GetDofRender(){
		return &m_DofRender;
	}
private:
	LPDIRECT3DSURFACE9 m_pMapZ = nullptr;		// 深度バッファ
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;		// バッファにコピーするためのテクスチャ
	LPDIRECT3DSURFACE9 m_pOriginalSurf = nullptr;	// サーフェス
	LPDIRECT3DSURFACE9 m_SavedMapZ;			// 深度バッファを保存しておくための変数
	LPDIRECT3DSURFACE9 m_SavedBuffer;			// バッファを保存しておくための変数
	CPrimitive m_copyBackBufferPrim;		//!<メインレンダーターゲットをバックバッファにコピーするときに使うプリミティブ。
	LPD3DXEFFECT m_pEffect;
	unsigned int m_bufferSize_Width;
	unsigned int m_bufferSize_Height;
	CCamera* m_pCamera = nullptr;
	CLight* m_pLight = nullptr;
	CBloomRender m_BloomRender;
	CDofRender m_DofRender;
	void DeleteAll(){};
};
