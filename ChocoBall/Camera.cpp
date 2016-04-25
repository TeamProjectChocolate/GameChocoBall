#include "stdafx.h"
#include "Camera.h"
#include "GraphicsDevice.h"
#include "Effect.h"

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

void CCamera::Initialize(){
	m_position.x = 0.0f;
	m_position.y = 1.2f;
	m_position.z = -20.0f;
	m_target.x = 0.0f;
	m_target.y = 0.1f;
	m_target.z = 0.0f;
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;
	m_ViewAngle = D3DXToRadian(45);		// 45度をラジアンに変換して格納
	m_aspect = 1.0f / 1.0f;				// アスペクト比に計算
	m_Near = 1.0f;						// どこから
	m_Far = 1000.0f;					// どこまで描画するか
}

void CCamera::Update(){
	// 射影マトリックスの設定
	D3DXMatrixIdentity(&m_Proj);			// 行列初期化
	D3DXMatrixPerspectiveFovLH(
		&m_Proj,							// 射影マトリックス
		m_ViewAngle,						// 画角
		m_aspect,							// アスペクト比
		m_Near,								// Nearプレーン
		m_Far);								// Farプレーン

	// ビュートランスフォーム(視点座標変換)
	D3DXMatrixIdentity(&m_View);									// 行列初期化
	D3DXVECTOR3 vEye(m_position.x, m_position.y, m_position.z);		// カメラ位置
	D3DXVECTOR3 vLookAt(m_target.x, m_target.y, m_target.z);		// 注視位置　カメラ向き
	D3DXVECTOR3 vUpVec(m_up.x, m_up.y, m_up.z);						// 上向き　カメラ傾き
	D3DXMatrixLookAtLH(&m_View, &vEye, &vLookAt, &vUpVec);			// ビューマトリックス設定
}

void CCamera::SetCamera(LPD3DXEFFECT effect){
	// ライト設定(白色、鏡面反射)
	D3DXVECTOR3 vDirec(0, -1, -1);		// ライト方向
	D3DLIGHT9 light;					// ライト構造体
	ZeroMemory(&light, sizeof(D3DLIGHT9));		// 初期化
	light.Type = D3DLIGHT_DIRECTIONAL;		// 平行光源
	// 拡散光
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	// 鏡面光
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vDirec);		// ライト方向の設定
	(*graphicsDevice()).SetLight(0, &light);			// ライト設定
	(*graphicsDevice()).LightEnable(0, TRUE);		// ライト当てる
	// Zバッファー、ライトの設定
	(*graphicsDevice()).SetRenderState(D3DRS_LIGHTING, TRUE);	// ライトを有効
	(*graphicsDevice()).SetRenderState(D3DRS_AMBIENT, 0x00aaaaaa);	// 環境光を設定
	(*graphicsDevice()).SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// 鏡面反射有効
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);			// Zバッファーを有効

	effect->SetMatrix("Proj"/*エフェクトファイル内の変数名*/, &m_Proj/*設定したい行列へのポインタ*/);
	effect->SetMatrix("View"/*エフェクトファイル内の変数名*/, &m_View/*設定したい行列へのポインタ*/);
}