#include "stdafx.h"
#include "C2DImage.h"
#include "GraphicsDevice.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"


void C2DImage::SetImage()
{
	IMAGE2D* Image = SINSTANCE(CImageManager)->Find2DImage(m_pFileName);
	if (Image != nullptr){
		m_pTexture = Image->pTex;
		m_rect = Image->rect;
		m_texCenter = D3DXVECTOR2(FLOAT(m_rect.right / 2), FLOAT(m_rect.bottom / 2));
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
	m_pEffect->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定

	//SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
	//ここで固定描画と同じように、ローカル座標に設定された頂点群をデバイスに渡す。通常と同じ方法。
	//	メッシュも同じく、マテリアルやテクスチャを設定
	//DrawSubset()を呼び出して描画

	(*graphicsDevice()).SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SVertex));
	(*graphicsDevice()).SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pEffect->SetMatrix("World"/*エフ5ェクトファイル内の変数名*/, &mWorld/*設定したい行列へのポインタ*/);

	m_pEffect->SetTexture("g_Texture", m_pTexture /*テクスチャ情報*/);

	m_pEffect->CommitChanges();				//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。

	(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	m_pEffect->EndPass();
	m_pEffect->End();

	//m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);		//スプライト描画開始
	//m_pSprite->SetTransform(&this->m_transformMatrix);	//変換行列セット
	//m_pSprite->Draw(this->m_pTexture, &this->m_rect, &D3DXVECTOR3(this->m_texCenter.x, this->m_texCenter.y, 0.0f), NULL, this->m_backColor);	//スプライトにテクスチャ貼付け
	//m_pSprite->End();	//スプライト描画終了
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
	D3DXMatrixTranslation(&matTrans, Transform.x, Transform.y, 0);
	D3DXMatrixRotationZ(&matRota, D3DXToRadian(m_transform.angle.z));
	mWorld = matScale * matRota * matTrans;
}