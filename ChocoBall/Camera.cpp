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
	m_target.y = 1.0f;
	m_target.z = 0.0f;
	m_up.x = 0.0f;
	m_up.y = 0.1f;
	m_up.z = 0.0f;
	m_ViewAngle = D3DXToRadian(45);		// 45度をラジアンに変換して格納
	m_aspect = 1.0f / 1.0f;		// アスペクト比に計算
	m_Near = 1.0f;		// どこから
	m_Far = 1000.0f;	// どこまで描画するか
}

void CCamera::Update(){
	// 射影マトリックスの設定
	D3DXMatrixIdentity(&m_Proj);			// 行列初期化
	D3DXMatrixPerspectiveFovLH(
		&m_Proj,				// 射影マトリックス
		m_ViewAngle,		// 画角
		m_aspect,				// アスペクト比
		m_Near,				// Nearプレーン
		m_Far);			// Farプレーン

	// ビュートランスフォーム(視点座標変換)
	D3DXMatrixIdentity(&m_View);					// 行列初期化
	D3DXVECTOR3 vEye(m_position.x, m_position.y, m_position.z);		// カメラ位置
	D3DXVECTOR3 vLookAt(m_target.x, m_target.y, m_target.z);		// 注視位置　カメラ向き
	D3DXVECTOR3 vUpVec(m_up.x, m_up.y, m_up.z);		// 上向き　カメラ傾き
	D3DXMatrixLookAtLH(&m_View, &vEye, &vLookAt, &vUpVec);	// ビューマトリックス設定
}

void CCamera::SetCamera(){
	SINSTANCE(CEffect)->GetEffect()->SetMatrix("Proj"/*エフェクトファイル内の変数名*/, &m_Proj/*設定したい行列へのポインタ*/);
	SINSTANCE(CEffect)->GetEffect()->SetMatrix("View"/*エフェクトファイル内の変数名*/, &m_View/*設定したい行列へのポインタ*/);
}