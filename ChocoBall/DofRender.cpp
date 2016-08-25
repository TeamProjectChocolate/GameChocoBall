#include "stdafx.h"
#include "DofRender.h"
#include "GraphicsDevice.h"
#include "RenderContext.h"
#include "ObjectManager.h"
#include "C3DImage.h"


CDofRender::CDofRender()
{
}


CDofRender::~CDofRender()
{
}

void CDofRender::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0; i<NUM_WEIGHTS; i++) {
		m_weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
		if (0 == i) {
			total += m_weights[i];
		}
		else {
			// 中心以外は、２回同じ係数を使うので２倍
			total += 2.0f*m_weights[i];
		}
	}
	// 規格化
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] /= total;
	}
};

/*!
* @brief	描画。
*/
void CDofRender::Draw(LPDIRECT3DTEXTURE9 tex)
{

	if (m_isEnable) {
		UpdateWeight(200.0f);
		LPDIRECT3DSURFACE9 RenderingTarget;
		LPDIRECT3DSURFACE9 m_SavedMapZ;

		// もとのレンダリングターゲットを保存
		(*graphicsDevice()).GetRenderTarget(0, &RenderingTarget);
		(*graphicsDevice()).GetDepthStencilSurface(&m_SavedMapZ);

		m_Primitive = SINSTANCE(CRenderContext)->GetPrimitive();

		// 深度情報抽出
		{
			(*graphicsDevice()).SetRenderTarget(0, m_DepthSamplingTarget);
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

			vector<OBJECT_DATA*> Objects = SINSTANCE(CObjectManager)->GetObjectList();
			int size = Objects.size();
			for (PRIORTY priorty = PRIORTY::PLAYER; priorty < PRIORTY::OBJECT2D; priorty = static_cast<PRIORTY>(priorty + 1)){	// 優先度の高いものから更新
				for (int idx = 0; idx < size; idx++){
					if (Objects[idx]->object->GetAlive()){
						if (Objects[idx]->priority == priorty){
							Objects[idx]->object->DrawDepth(m_pEffect,m_FarNear);
							//static_cast<C3DImage*>(Objects[idx]->object)->DrawDepth();
							//if (/*アニメーションするか*/){
							//	//(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

							//}
							//else{

							//	//(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
							//}
						}
					}
				}
			}
		}
		int w = SINSTANCE(CRenderContext)->GetWindowWidth();
		int h = SINSTANCE(CRenderContext)->GetWindowHeight();

		//XBlur
		{
			(*graphicsDevice()).SetRenderTarget(0, m_RenderTarget[0]);
			//(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique("XBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			float size[2] = {
				static_cast<float>(w),
				static_cast<float>(h)
			};
			float offset[] = {
				16.0f / static_cast<float>(w),
				0.0f
			};
			m_pEffect->SetValue("g_TexSize", size, sizeof(size));
			m_pEffect->SetValue("g_offset", offset, sizeof(offset));
			m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture("g_blur", tex);
			m_pEffect->CommitChanges();

			(*graphicsDevice()).SetVertexDeclaration(m_Primitive->GetVertexDecl());
			(*graphicsDevice()).SetStreamSource(0, m_Primitive->GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
			(*graphicsDevice()).SetIndices(m_Primitive->GetIndexBuffer());

			(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			m_pEffect->EndPass();
			m_pEffect->End();

		}
		//YBlur
		{
			(*graphicsDevice()).SetRenderTarget(0, m_RenderTarget[1]);
			//(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique("YBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			float size[2] = {
				static_cast<float>(w),
				static_cast<float>(h)
			};
			float offset[] = {
				0.0f,
				16.0f / static_cast<float>(h)
			};
			m_pEffect->SetValue("g_TexSize", size, sizeof(size));
			m_pEffect->SetValue("g_offset", offset, sizeof(offset));
			m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture("g_blur", m_pBlurTexture[0]);
			m_pEffect->CommitChanges();
			(*graphicsDevice()).SetVertexDeclaration(m_Primitive->GetVertexDecl());
			(*graphicsDevice()).SetStreamSource(0, m_Primitive->GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
			(*graphicsDevice()).SetIndices(m_Primitive->GetIndexBuffer());

			(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			m_pEffect->EndPass();
			m_pEffect->End();
		}

		{
			float offset[] = {
				0.5f / static_cast<float>(w),
				0.5f / static_cast<float>(h)
			};
			//戻す。
			(*graphicsDevice()).SetRenderTarget(0, RenderingTarget);
			(*graphicsDevice()).SetDepthStencilSurface(m_SavedMapZ);

			//深度情報を参照して合成。
			m_pEffect->SetTechnique("Final");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			m_pEffect->SetTexture("g_Texture", tex);
			m_pEffect->SetTexture("g_DepthSample", m_pDepthSamplingTexture);
			m_pEffect->SetTexture("g_blur", m_pBlurTexture[1]);
			m_pEffect->SetValue("g_offset", offset, sizeof(offset));
			m_pEffect->CommitChanges();
			(*graphicsDevice()).SetVertexDeclaration(m_Primitive->GetVertexDecl());
			(*graphicsDevice()).SetStreamSource(0, m_Primitive->GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
			(*graphicsDevice()).SetIndices(m_Primitive->GetIndexBuffer());

			(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			m_pEffect->EndPass();
			m_pEffect->End();
		}
	}

};

/*!
* @brief	作成。
*/
void CDofRender::Create()
{
	int w = SINSTANCE(CRenderContext)->GetWindowWidth();
	int h = SINSTANCE(CRenderContext)->GetWindowHeight();

	//レンダリングターゲットを作成。
	//深度情報抽出用
	(*graphicsDevice()).CreateDepthStencilSurface(w, h, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_DepthSamplingTarget, NULL);
	(*graphicsDevice()).CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pDepthSamplingTexture, NULL);
	m_pDepthSamplingTexture->GetSurfaceLevel(0, &m_DepthSamplingTarget);
	//横ブラー用。
	(*graphicsDevice()).CreateDepthStencilSurface(w, h, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_RenderTarget[0], NULL);
	(*graphicsDevice()).CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pBlurTexture[0], NULL);
	m_pBlurTexture[0]->GetSurfaceLevel(0, &m_RenderTarget[0]);
	//縦ブラー用。
	(*graphicsDevice()).CreateDepthStencilSurface(w, h, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_RenderTarget[1], NULL);
	(*graphicsDevice()).CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pBlurTexture[1], NULL);
	m_pBlurTexture[1]->GetSurfaceLevel(0, &m_RenderTarget[1]);

	m_pEffect = SINSTANCE(CEffect)->LoadEffect(_T("Shader/DepthOfField.hlsl"));

	m_FarNear = D3DXVECTOR2(100.0f, 1.0f);
	m_isEnable = true;
};
