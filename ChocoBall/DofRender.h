#pragma once
#include "stdafx.h"
#include "Effect.h"
#include "Primitive.h"


class CDofRender
{
public:
	CDofRender();
	~CDofRender();
	/*!
	* @brief	描画。
	*/
	void Draw(LPDIRECT3DTEXTURE9);
	/*!
	* @brief	作成。
	*/
	void Create();
	LPDIRECT3DTEXTURE9 GetDepthTex(){
		return m_pDepthSamplingTexture;
	}
private:
	/*!
	* @brief	ガウスフィルタの重みを更新。
	*/
	void UpdateWeight(float dispersion);
private:
	static const int NUM_WEIGHTS = 8;
	LPD3DXEFFECT	m_pEffect;						//!<エフェクト。
	LPDIRECT3DSURFACE9 m_DepthSamplingTarget;	// 深度情報抽出用レンダリングターゲット
	LPDIRECT3DTEXTURE9 m_pDepthSamplingTexture;	// 深度情報を書き込むテクスチャ
	LPDIRECT3DSURFACE9	m_RenderTarget[2];	//!<ぼかすためのレンダリングターゲット。
	LPDIRECT3DTEXTURE9 m_pBlurTexture[2];	// ぼかしたテクスチャ(X方向のぼかしとY方向のぼかしで二つ)
	bool			m_isEnable;						//!<有効？
	float				m_weights[NUM_WEIGHTS];
	CPrimitive* m_Primitive;
	D3DXVECTOR2 m_FarNear;
};

