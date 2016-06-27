#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Camera.h"

class CShadowRender
{
	SINGLETON_DECL(CShadowRender)
public:
	// 影を生成するオブジェクトを登録する関数
	// 引き数： C3DImage* C3DImageを継承したクラスのポインタ
	// 返り値： なし
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
		m_camera.SetFarNear(effect);
	}
	void DrawFrame(/*LPDIRECT3DDEVICE9, */LPD3DXFRAME,C3DImage*);
	void DrawMeshContainer(/*LPDIRECT3DDEVICE9,*/ LPD3DXMESHCONTAINER,C3DImage*/*, LPD3DXFRAME*/);
	void AnimationDraw(D3DXMESHCONTAINER_DERIVED*,C3DImage*);
	void NonAnimationDraw(C3DImage*);
	void DeleteObject(C3DImage*);
	void CleanManager();
	void ExcuteDeleteObjects();
private:
	LPDIRECT3DSURFACE9 m_pMapZ = nullptr;			// 深度バッファ
	LPDIRECT3DTEXTURE9 m_pShadow = nullptr;		// 影を落とすためのテクスチャ
	LPDIRECT3DSURFACE9 m_pOriginalSurf = nullptr;	// サーフェス
	LPD3DXEFFECT m_pEffect = nullptr;
	vector<C3DImage*> m_ShadowObjects;	// 影を生成したいオブジェクトの配列
	vector<C3DImage*> m_DeleteObjects;
	D3DXVECTOR3 m_target;		// 影を生成したいオブジェクトのポジション
	D3DXVECTOR3 m_ShadowLightPos;		// 影を描画するためのカメラのポジション
	D3DXVECTOR3 m_ShadowLightDirection;		// 影を描画するためのカメラの向き
	CCamera m_camera;
	D3DXMATRIX m_View;					// ライトのビュー行列
	D3DXMATRIX m_Proj;					// ライトのプロジェクション行列
	void DeleteAll();
};

