#include "stdafx.h"
#include "BloomRender.h"
#include "GraphicsDevice.h"]
#include "RenderContext.h"


CBloomRender::CBloomRender()
{
};


CBloomRender::~CBloomRender()
{
};


void CBloomRender::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0; i<NUM_WEIGHTS; i++) {
		m_weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
		if (0 == i) {
			total += m_weights[i];
		}
		else {
			// ���S�ȊO�́A�Q�񓯂��W�����g���̂łQ�{
			total += 2.0f*m_weights[i];
		}
	}
	// �K�i��
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] /= total;
	}
};

/*!
* @brief	�`��B
*/
void CBloomRender::Draw()
{

	if (m_isEnable) {
		UpdateWeight(25.0f);
		LPDIRECT3DSURFACE9 RenderingTarget;
		LPDIRECT3DSURFACE9 m_SavedMapZ;

		// ���Ƃ̃����_�����O�^�[�Q�b�g��ۑ�
		(*graphicsDevice()).GetRenderTarget(0, &RenderingTarget);
		(*graphicsDevice()).GetDepthStencilSurface(&m_SavedMapZ);

		m_Primitive = SINSTANCE(CRenderContext)->GetPrimitive();
		//�P�x���o
		{
			(*graphicsDevice()).SetRenderTarget(0, m_luminanceRenderTarget);
			(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0, 1.0f, 0);
			m_pEffect->SetTechnique("SamplingLuminance");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			m_pEffect->SetTexture("g_scene",SINSTANCE(CRenderContext)->GetTexture());
			m_pEffect->CommitChanges();

			(*graphicsDevice()).SetVertexDeclaration(m_Primitive->GetVertexDecl());
			(*graphicsDevice()).SetStreamSource(0, m_Primitive->GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
			(*graphicsDevice()).SetIndices(m_Primitive->GetIndexBuffer());

			(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			m_pEffect->EndPass();
			m_pEffect->End();

		}
		//XBlur
		{
			(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[0]);
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique("XBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			float size[2] = {
				static_cast<float>(SINSTANCE(CRenderContext)->GetWindowWidth()),
				static_cast<float>(SINSTANCE(CRenderContext)->GetWindowHeight())
			};
			float offset[] = {
				16.0f / static_cast<float>(SINSTANCE(CRenderContext)->GetWindowWidth()),
				0.0f
			};
			m_pEffect->SetValue("g_luminanceTexSize", size, sizeof(size));
			m_pEffect->SetValue("g_offset", offset, sizeof(offset));
			m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture("g_blur", m_pluminanceTexture);
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
			(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[1]);
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique("YBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			float size[2] = {
				static_cast<float>(m_size[0].w),
				static_cast<float>(m_size[0].h)
			};
			float offset[] = {
				0.0f,
				16.0f / static_cast<float>(m_size[0].h)
			};
			m_pEffect->SetValue("g_luminanceTexSize", size, sizeof(size));
			m_pEffect->SetValue("g_offset", offset, sizeof(offset));
			m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture("g_blur", m_pTexture[0]);
			m_pEffect->CommitChanges();
			(*graphicsDevice()).SetVertexDeclaration(m_Primitive->GetVertexDecl());
			(*graphicsDevice()).SetStreamSource(0, m_Primitive->GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
			(*graphicsDevice()).SetIndices(m_Primitive->GetIndexBuffer());

			(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			m_pEffect->EndPass();
			m_pEffect->End();
		}

		//XBlur2
		{
			(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[2]);
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique("XBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			float size[2] = {
				static_cast<float>(m_size[1].w),
				static_cast<float>(m_size[1].h)
			};
			float offset[] = { 
				16.0f / static_cast<float>(m_size[1].w),
				0.0f
			};
			m_pEffect->SetValue("g_luminanceTexSize", size, sizeof(size));
			m_pEffect->SetValue("g_offset", offset, sizeof(offset));
			m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture("g_blur", m_pTexture[1]);
			m_pEffect->CommitChanges();
			(*graphicsDevice()).SetVertexDeclaration(m_Primitive->GetVertexDecl());
			(*graphicsDevice()).SetStreamSource(0, m_Primitive->GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
			(*graphicsDevice()).SetIndices(m_Primitive->GetIndexBuffer());

			(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			m_pEffect->EndPass();
			m_pEffect->End();

		}
		//YBlur2
		{
			(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[3]);
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique( "YBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass( 0);
			float size[2] = {
				static_cast<float>(m_size[2].w)	,
				static_cast<float>(m_size[2].h)
			};
			float offset[] = {
				0.0f,
				16.0f / static_cast<float>(m_size[2].h)
			};
			m_pEffect->SetValue("g_luminanceTexSize", size, sizeof(size));
			m_pEffect->SetValue("g_offset", offset, sizeof(offset));
			m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture("g_blur", m_pTexture[2]);
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
				0.5f / static_cast<float>(m_size[3].w),
				0.5f / static_cast<float>(m_size[3].h)
			};
			//�߂��B
			(*graphicsDevice()).SetRenderTarget(0, RenderingTarget);
			(*graphicsDevice()).SetDepthStencilSurface(m_SavedMapZ);

			//���Z�����B
			(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			m_pEffect->SetTechnique("Final");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			m_pEffect->SetTexture("g_blur", m_pTexture[3]);
			m_pEffect->SetValue("g_offset", offset, sizeof(offset));
			m_pEffect->CommitChanges();
			(*graphicsDevice()).SetVertexDeclaration(m_Primitive->GetVertexDecl());
			(*graphicsDevice()).SetStreamSource(0, m_Primitive->GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
			(*graphicsDevice()).SetIndices(m_Primitive->GetIndexBuffer());

			(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			m_pEffect->EndPass();
			m_pEffect->End();

			(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		}
	}

};

/*!
* @brief	�쐬�B
*/
void CBloomRender::Create()
{
	int w = SINSTANCE(CRenderContext)->GetWindowWidth();
	int h = SINSTANCE(CRenderContext)->GetWindowHeight();
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬�B
	// �����_�����O�^�[�Q�b�g����
	(*graphicsDevice()).CreateDepthStencilSurface(w, h, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_luminanceRenderTarget, NULL);
	(*graphicsDevice()).CreateTexture(w,h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pluminanceTexture, NULL);
	m_pluminanceTexture->GetSurfaceLevel(0, &m_luminanceRenderTarget);

	//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
	//���u���[�p�B
	m_size[0].w = w >> 1;
	m_size[0].h = h;
	(*graphicsDevice()).CreateDepthStencilSurface(m_size[0].w,m_size[0].h, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_downSamplingRenderTarget[0], NULL);
	(*graphicsDevice()).CreateTexture(m_size[0].w, m_size[0].h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture[0], NULL);
	m_pTexture[0]->GetSurfaceLevel(0, &m_downSamplingRenderTarget[0]);
	//�c�u���[�p�B
	m_size[1].w = w >> 1;
	m_size[1].h = h >> 1;
	(*graphicsDevice()).CreateDepthStencilSurface(m_size[1].w, m_size[1].h, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_downSamplingRenderTarget[1], NULL);
	(*graphicsDevice()).CreateTexture(m_size[1].w, m_size[1].h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture[1], NULL);
	m_pTexture[1]->GetSurfaceLevel(0, &m_downSamplingRenderTarget[1]);
	//���u���[�p�B
	m_size[2].w = w >> 2;
	m_size[2].h = h;
	(*graphicsDevice()).CreateDepthStencilSurface(m_size[2].w, m_size[2].h, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_downSamplingRenderTarget[2], NULL);
	(*graphicsDevice()).CreateTexture(m_size[2].w, m_size[2].h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture[2], NULL);
	m_pTexture[2]->GetSurfaceLevel(0, &m_downSamplingRenderTarget[2]);
	//�c�u���[�p�B
	m_size[3].w = w >> 2;
	m_size[3].h = h >> 2;
	(*graphicsDevice()).CreateDepthStencilSurface(m_size[3].w,m_size[3].h, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_downSamplingRenderTarget[3], NULL);
	(*graphicsDevice()).CreateTexture(m_size[3].w, m_size[3].h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture[3], NULL);
	m_pTexture[3]->GetSurfaceLevel(0, &m_downSamplingRenderTarget[3]);

	m_pEffect = SINSTANCE(CEffect)->LoadEffect(_T("Shader/Bloom.hlsl"));
	m_isEnable = true;
};
