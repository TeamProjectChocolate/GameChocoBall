#include "stdafx.h"
#include "C2DImage.h"
#include "GraphicsDevice.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"


void C2DImage::SetImage()
{
	m_pImage = SINSTANCE(CImageManager)->Find2DImage(m_pFileName);
}


void C2DImage::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/2DShader.hlsl"));	// 使用するshaderファイルを指定(デフォルト)
	SVertex vertices[] = {
		{ -1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f, },
		{ -1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f, },
		{ 1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f, },
		{ 1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f, },
		{ -1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f, },
		{ 1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f, },
	};

	(*graphicsDevice()).CreateVertexBuffer(6 * sizeof(SVertex), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);
	VOID* pVertices;
	m_pVertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVertexBuffer->Unlock();
}

void C2DImage::Draw()
{
	SetUpTechnique();
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);

	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pEffect->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定


	//SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
	//ここで固定描画と同じように、ローカル座標に設定された頂点群をデバイスに渡す。通常と同じ方法。
	//	メッシュも同じく、マテリアルやテクスチャを設定
	//DrawSubset()を呼び出して描画

	(*graphicsDevice()).SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SVertex));
	(*graphicsDevice()).SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pEffect->SetMatrix("World", &mWorld);
	m_pEffect->SetInt("Split_X", m_Split.x);
	m_pEffect->SetInt("Split_Y", m_Split.y);
	m_pEffect->SetInt("NowCol", m_Now.x);
	m_pEffect->SetInt("NowRow", m_Now.y);

	float ratio_X = m_pImage->RealSize.x / m_pImage->UnRealSize.x;
	float ratio_Y = m_pImage->RealSize.y / m_pImage->UnRealSize.y;

	m_pEffect->SetFloat("Ratio_X", ratio_X);
	m_pEffect->SetFloat("Ratio_Y", ratio_Y);
	
	m_pEffect->SetTexture("g_Texture", m_pImage->pTex /*テクスチャ情報*/);

	m_pEffect->SetFloat("Alpha", GetAlpha());
	//m_pEffect->SetFloat("g_brightness", m_brightness);
	m_pEffect->CommitChanges();				//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。

	(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	m_pEffect->EndPass();
	m_pEffect->End();
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void C2DImage::SetupMatrices()
{
	D3DXVECTOR3 Scale;
	Scale.x = m_transform.scale.x / WINDOW_WIDTH;
	Scale.y = m_transform.scale.y / WINDOW_HEIGHT;
	D3DXVECTOR3 Transform;
	Transform.x = m_transform.position.x / WINDOW_WIDTH;
	Transform.y = m_transform.position.y / WINDOW_HEIGHT;
	Transform.x = -1.0f + Transform.x * 2.0f;
	Transform.y = 1.0f - Transform.y * 2.0f;

	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	D3DXMATRIX matRota;
	D3DXMatrixIdentity(&this->mWorld);	//ワールド行列初期化
	D3DXMatrixScaling(&matScale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationQuaternion(&matRota, &m_transform.angle);
	//D3DXMatrixRotationZ(&matRota, D3DXToRadian(m_transform.angle.z));
	D3DXMatrixTranslation(&matTrans, Transform.x, Transform.y, 0);
	mWorld = matScale * matRota * matTrans;
}

