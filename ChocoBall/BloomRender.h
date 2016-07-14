#pragma once
#include "stdafx.h"
#include "Effect.h"
#include "Primitive.h"

//#define USE_LOW_QUALITY_BLOOM		//定義で低クォリティのブルーム処理が有効になる。品質は劣化する。

typedef struct int2{
	int w;
	int h;
};

class CBloomRender
{
public:
	CBloomRender();
	~CBloomRender();
	/*!
	* @brief	描画。
	*/
	void Draw();
	/*!
	* @brief	作成。
	*/
	void Create();

	LPDIRECT3DTEXTURE9 GetTexture(){
		return m_pluminanceTexture;
	}
private:
	/*!
	* @brief	ガウスフィルタの重みを更新。
	*/
	void UpdateWeight(float dispersion);
private:
#if defined(USE_LOW_QUALITY_BLOOM)
	static const int NUM_WEIGHTS = 4;
#else
	static const int NUM_WEIGHTS = 8;
#endif
	LPD3DXEFFECT	m_pEffect;						//!<エフェクト。
	LPDIRECT3DSURFACE9	m_luminanceRenderTarget;		//!<輝度を抽出するレンダリングターゲット。
	LPDIRECT3DSURFACE9	m_downSamplingRenderTarget[4];	//!<輝度をダウンサンプリングするためのレンダリングターゲット。
	LPDIRECT3DTEXTURE9 m_pluminanceTexture;
	LPDIRECT3DTEXTURE9 m_pTexture[4];
	bool			m_isEnable;						//!<有効？
	float				m_weights[NUM_WEIGHTS];
	CPrimitive* m_Primitive;
	int2 m_size[4];
};

