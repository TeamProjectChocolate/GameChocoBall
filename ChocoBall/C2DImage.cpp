#include "stdafx.h"
#include "C2DImage.h"
#include "GraphicsDevice.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"


void C2DImage::SetImage()
{
	IMAGE2D* Image = SINSTANCE(CImageManager)->Find2DImage(m_pFileName);
	m_pTexture = Image->pTex;
	m_rect = Image->rect;
	m_texCenter = D3DXVECTOR2(FLOAT(m_rect.right / 2), FLOAT(m_rect.bottom / 2));
}


void C2DImage::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/2DShader.hlsl"));	// �g�p����shader�t�@�C�����w��(�f�t�H���g)
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

	m_pEffect->BeginPass(0);	//�p�X�̔ԍ����w�肵�Ăǂ̃p�X���g�p���邩�w��


	//SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
	//�����ŌŒ�`��Ɠ����悤�ɁA���[�J�����W�ɐݒ肳�ꂽ���_�Q���f�o�C�X�ɓn���B�ʏ�Ɠ������@�B
	//	���b�V�����������A�}�e���A����e�N�X�`����ݒ�
	//DrawSubset()���Ăяo���ĕ`��

	(*graphicsDevice()).SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SVertex));
	(*graphicsDevice()).SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pEffect->SetMatrix("World"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &mWorld/*�ݒ肵�����s��ւ̃|�C���^*/);

	m_pEffect->SetTexture("g_Texture", m_pTexture /*�e�N�X�`�����*/);

	m_pEffect->SetFloat("Alpha", GetAlpha());
	m_pEffect->CommitChanges();				//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B

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
	D3DXMatrixIdentity(&this->mWorld);	//���[���h�s�񏉊���
	D3DXMatrixScaling(&matScale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationQuaternion(&matRota, &m_transform.angle);
	//D3DXMatrixRotationZ(&matRota, D3DXToRadian(m_transform.angle.z));
	D3DXMatrixTranslation(&matTrans, Transform.x, Transform.y, 0);
	mWorld = matScale * matRota * matTrans;
}