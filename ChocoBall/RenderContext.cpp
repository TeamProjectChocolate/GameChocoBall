#include "stdafx.h"
#include "RenderContext.h"
#include "GraphicsDevice.h"
#include "Effect.h"

CRenderContext* CRenderContext::m_instance = nullptr;


void CRenderContext::CreateRenderingTerget(){
	static SShapeVertex_PT vertex[]{
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	static unsigned short index[] = {
		0, 1, 2, 3
	};
	m_copyBackBufferPrim.Create(
		EType::eTriangleStrip,
		4,
		sizeof(SShapeVertex_PT),
		scShapeVertex_PT_Element,
		vertex,
		4,
		D3DFMT_INDEX16,
		index
		);

	m_pMapZ = nullptr;
	m_pTexture = nullptr;
	m_pOriginalSurf = nullptr;
	m_bufferSize_Width = WINDOW_WIDTH * 2;
	m_bufferSize_Height = WINDOW_HEIGHT * 2;

	
	// �����_�����O�^�[�Q�b�g����
	(*graphicsDevice()).CreateDepthStencilSurface(m_bufferSize_Width, m_bufferSize_Height, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pMapZ, NULL);
	(*graphicsDevice()).CreateTexture(m_bufferSize_Width, m_bufferSize_Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture, NULL);
	m_pTexture->GetSurfaceLevel(0, &m_pOriginalSurf);

	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/TransformedShader.hlsl"));
}

void CRenderContext::RenderingStart(){
	// ���Ƃ̃����_�����O�^�[�Q�b�g��ۑ�
	(*graphicsDevice()).GetRenderTarget(0, &m_SavedBuffer);
	(*graphicsDevice()).GetDepthStencilSurface(&m_SavedMapZ);

	// �����_�����O�^�[�Q�b�g�̕ύX
	(*graphicsDevice()).SetRenderTarget(0, m_pOriginalSurf);
	(*graphicsDevice()).SetDepthStencilSurface(m_pMapZ);

	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
}

void CRenderContext::RenderingEnd(){
	// �����_�����O�^�[�Q�b�g�����ɖ߂�
	(*graphicsDevice()).SetRenderTarget(0, m_SavedBuffer);
	(*graphicsDevice()).SetDepthStencilSurface(m_SavedMapZ);
}

void CRenderContext::SetRenderingBuffer(){
	m_pEffect->SetTechnique("TransformedPrim");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	float offset[] = {
		0.5f / m_bufferSize_Width,
		0.5f / m_bufferSize_Height
	};

	m_pEffect->SetValue("g_offset", offset, sizeof(offset));
	m_pEffect->SetTexture("g_tex",m_pTexture);
	m_pEffect->CommitChanges();				//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
	
	(*graphicsDevice()).SetFVF(D3DFVF_CUSTOMVERTEX);

	(*graphicsDevice()).SetVertexDeclaration(m_copyBackBufferPrim.GetVertexDecl());
	(*graphicsDevice()).SetStreamSource(0, m_copyBackBufferPrim.GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
	(*graphicsDevice()).SetIndices(m_copyBackBufferPrim.GetIndexBuffer());

	(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	m_pEffect->EndPass();
	m_pEffect->End();
}

