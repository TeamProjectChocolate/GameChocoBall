#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Camera.h"

class CShadowRender
{
	SINGLETON_DECL(CShadowRender)
public:
	void Entry(C3DImage*);
	void Initialize();
	void Update();
	void Draw();
	void SetObjectPos(D3DXVECTOR3 pos){
		m_target = pos;
	}
	void SetShadowCameraPos(D3DXVECTOR3 pos){
		m_ShadowLightPos = pos;
	}
	void SetShadowCameraDir(D3DXVECTOR3 dir){
		m_ShadowLightDirection = dir;
	}
	LPDIRECT3DTEXTURE9 GetTexture(){
		return m_pShadow;
	}
	void SetShadowCamera(LPD3DXEFFECT effect){
		effect->SetMatrix("LightViewProj", &(m_camera.GetView() * m_camera.GetProj()));
	}
private:
	LPDIRECT3DSURFACE9 m_pMapZ;			// 深度バッファ
	LPDIRECT3DTEXTURE9 m_pShadow;		// 影を落とすためのテクスチャ
	LPDIRECT3DSURFACE9 m_pOriginalSurf;	// サーフェス
	LPD3DXEFFECT m_pEffect;
	vector<C3DImage*> m_ShadowObjects;	// 影を生成したいオブジェクトの配列
	D3DXVECTOR3 m_target;		// 影を生成したいオブジェクトのポジション
	D3DXVECTOR3 m_ShadowLightPos;		// 影を描画するためのカメラのポジション
	D3DXVECTOR3 m_ShadowLightDirection;		// 影を描画するためのカメラの向き
	CCamera m_camera;
	D3DXMATRIX m_View;					// ライトのビュー行列
	D3DXMATRIX m_Proj;					// ライトのプロジェクション行列
	void DeleteAll();
};

