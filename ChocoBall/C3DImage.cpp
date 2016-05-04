#include "stdafx.h"
#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"
#include "GraphicsDevice.h"
#include "ShadowRender.h"

HRESULT C3DImage::SetImage(){

	m_pImage = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (m_pImage != nullptr){
		return S_OK;
	}

	LoadXFile();
	return S_OK;
}

HRESULT C3DImage::LoadXFile(){
	DWORD i;
	LPD3DXBUFFER pMaterials;
	DWORD NumMaterials;
	LPD3DXMESH pMesh;

	// X�t�@�C�����[�h
	if (FAILED(D3DXLoadMeshFromX(m_pFileName, D3DXMESH_MANAGED, graphicsDevice(), NULL, &pMaterials, NULL, &NumMaterials, &pMesh))){		// X�t�@�C���ǂݎ��
		return E_FAIL;
	};

	// X�t�@�C���ɖ@�����Ȃ��ꍇ�́A�@������������
	if (!(pMesh->GetFVF() & D3DFVF_NORMAL)){
		ID3DXMesh* pTempMesh = NULL;
		pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF() | D3DFVF_NORMAL, graphicsDevice(), &pTempMesh);
		D3DXComputeNormals(pTempMesh, NULL);
		pMesh->Release();
		pMesh = pTempMesh;
	}
	// ���_�錾
	const D3DVERTEXELEMENT9 vertexDecl[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 }, 
		{ 0, 56, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};

	LPD3DXMESH pCloneMesh = nullptr;

	pMesh->CloneMesh(pMesh->GetOptions(), vertexDecl, &(*graphicsDevice()), &pCloneMesh);
	D3DXComputeTangentFrameEx(pCloneMesh,
		D3DDECLUSAGE_TEXCOORD,
		0,
		D3DDECLUSAGE_TANGENT,
		0,
		D3DDECLUSAGE_BINORMAL,
		0,
		D3DDECLUSAGE_NORMAL,
		0,
		0,
		NULL,
		0.01f,    //�{�P�.�l��������������Ƃڂ��Ȃ��Ȃ�
		0.25f,
		0.01f,
		&pCloneMesh,
		NULL
		);

	pMesh->Release();
	pMesh = pCloneMesh;

	// �}�e���A���A�e�N�X�`���̏���
	D3DMATERIAL9* pMeshMat = new D3DMATERIAL9[NumMaterials];		// ���b�V�������m��
	LPDIRECT3DTEXTURE9* pMeshTex = new LPDIRECT3DTEXTURE9[NumMaterials];		// �e�N�X�`�����m��

	D3DXMATERIAL* d3Mat = (D3DXMATERIAL*)pMaterials->GetBufferPointer();

	for (i = 0; i < NumMaterials; i++){
		pMeshMat[i] = d3Mat[i].MatD3D;		// �}�e���A�����Z�b�g
		pMeshMat[i].Ambient = pMeshMat[i].Diffuse;		// ����������

		pMeshTex[i] = NULL;		// �e�N�X�`��������
		if (d3Mat[i].pTextureFilename != NULL && lstrlen(d3Mat[i].pTextureFilename) > 0){		// �g�p���Ă���e�N�X�`��������Γǂݍ���

			if (FAILED(D3DXCreateTextureFromFile(graphicsDevice(), d3Mat[i].pTextureFilename, &pMeshTex[i]))){
				return E_FAIL;
			}
		}
	}

	SINSTANCE(CImageManager)->Add3D(m_pFileName, pMeshMat, pMeshTex, NumMaterials, pMesh);		// IMAGE���z��ɒǉ�
	m_pImage = new IMAGE3D;
	m_pImage->NumMaterials = NumMaterials;
	m_pImage->pMat = pMeshMat;
	m_pImage->pMesh = pMesh;
	m_pImage->ppTex = pMeshTex;

	pMaterials->Release();		// �}�e���A�������
	return S_OK;
}

void C3DImage::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// �g�p����shader�t�@�C�����w��(�f�t�H���g)

	m_lightDir[0] = D3DXVECTOR3(0.707f, 0.707f, 0.0f);
	m_lightDir[1] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_lightDir[2] = D3DXVECTOR3(1.0f, -1.0f, 0.5f);
	m_lightDir[3] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(m_lightDir[0].x, m_lightDir[0].y, m_lightDir[0].z, 0.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(m_lightDir[1].x, m_lightDir[1].y, m_lightDir[1].z, 0.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(m_lightDir[2].x, m_lightDir[2].y, m_lightDir[2].z, 0.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(m_lightDir[3].x, m_lightDir[3].y, m_lightDir[3].z, 0.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.2f, 0.0f, 0.0f,100.0f));

	count = 0;
	dir = D3DXVECTOR3(1,1,1);
}

void C3DImage::Update(){

	if (m_lightDir[0].x > 1.0f){
		dir.x *= -1;
	}
	else if (m_lightDir[0].x < -1.0f){
		dir.x *= -1;
	}
	m_lightDir[0].x += 0.1f * dir.x;

	if (m_lightDir[0].y > 1.0f){
		dir.y *= -1;
	}
	else if (m_lightDir[0].y < -1.0f){
		dir.y *= -1;
	}
	m_lightDir[0].y += 0.1f * dir.y;

	if (m_lightDir[0].z > 1.0f){
		dir.z *= -1;
	}
	else if (m_lightDir[0].z < -1.0f){
		dir.z *= -1;
	}
	m_lightDir[0].z += 0.1f * dir.z;

	if (count % 60 == 0){
		D3DXVECTOR3 work = m_lightDir[0];
		m_lightDir[0] = m_lightDir[1];
		m_lightDir[1] = m_lightDir[2];
		m_lightDir[2] = m_lightDir[3];
		m_lightDir[3] = work;
		count = 0;
	}

	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(m_lightDir[0].x, m_lightDir[0].y, m_lightDir[0].z, 0.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(m_lightDir[1].x, m_lightDir[1].y, m_lightDir[1].z, 0.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(m_lightDir[2].x, m_lightDir[2].y, m_lightDir[2].z, 0.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(m_lightDir[3].x, m_lightDir[3].y, m_lightDir[3].z, 0.0f));

	count++;


	D3DXMATRIX Trans;	// �ړ��s��
	D3DXMATRIX Scale;	// �g��E�k���s��

	D3DXMatrixIdentity(&m_World);	// �s�񏉊���

	D3DXMatrixRotationX(&m_Rota, m_transform.angle.x);
	D3DXMatrixMultiply(&m_World, &m_World, &m_Rota);

	D3DXMatrixRotationY(&m_Rota, m_transform.angle.y);
	D3DXMatrixMultiply(&m_World, &m_World, &m_Rota);

	D3DXMatrixRotationZ(&m_Rota, m_transform.angle.z);
	D3DXMatrixMultiply(&m_World, &m_World, &m_Rota);

	m_Rota = m_World;

	D3DXMatrixScaling(&Scale, m_transform.scale.x, m_transform.scale.y, m_transform.scale.z);
	D3DXMatrixMultiply(&m_World, &m_World, &Scale);

	D3DXMatrixTranslation(&Trans, m_transform.position.x, m_transform.position.y, m_transform.position.z);
	D3DXMatrixMultiply(&m_World, &m_World, &Trans);

}

void C3DImage::Draw(){

	if (m_pImage->ppTex[0] == nullptr){
		m_pEffect->SetTechnique("NotNormalMapBasicTec");
	}

	UINT numPass;
	m_pEffect->Begin(&numPass/*�e�N�j�b�N���ɒ�`����Ă���p�X�̐����ԋp�����*/, 0);
	m_pEffect->BeginPass(0);	//�p�X�̔ԍ����w�肵�Ăǂ̃p�X���g�p���邩�w��

	// �����x�L����
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���݂̃v���W�F�N�V�����s��ƃr���[�s����V�F�[�_�[�ɓ]��
	SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);

	// �f�B�t���[�Y���C�g�̌������V�F�[�_�[�ɓ]��
	m_pEffect->SetVectorArray("diffuseLightDirection", m_light.GetDiffuseLightDirection(), NUM_DIFFUSE_LIGHT);
	// �f�B�t���[�Y���C�g�̃J���[���V�F�[�_�[�ɓ]��
	m_pEffect->SetVectorArray("diffuseLightColor", m_light.GetDiffuseLightColor(), NUM_DIFFUSE_LIGHT);
	// �������V�F�[�_�[�ɓ]��
	m_pEffect->SetVector("ambientLight", &m_light.GetAmbientLight());
	// ���_���V�F�[�_�[�ɓ]��
	m_pEffect->SetVector("EyePosition", reinterpret_cast<D3DXVECTOR4*>(&SINSTANCE(CRenderContext)->GetCurrentCamera()->GetPos()));

	SINSTANCE(CShadowRender)->SetShadowCamera(m_pEffect);
	//�����ŌŒ�`��Ɠ����悤�ɁA���[�J�����W�ɐݒ肳�ꂽ���_�Q���f�o�C�X�ɓn���B�ʏ�Ɠ������@�B
	//	���b�V�����������A�}�e���A����e�N�X�`����ݒ�
	//DrawSubset()���Ăяo���ĕ`��

	// ���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	// ���[���h�s�񐶐�


	m_pEffect->SetMatrix("Rota", &m_Rota);
	m_pEffect->SetMatrix("World"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &m_World/*�ݒ肵�����s��ւ̃|�C���^*/);

	m_pEffect->SetFloat("Alpha", GetAlpha());

	// ���_�t�H�[�}�b�g���Z�b�g
	(*graphicsDevice()).SetFVF(m_pImage->pMesh->GetFVF());

	for (DWORD i = 0; i < m_pImage->NumMaterials; i++){
		m_pEffect->SetTexture("g_ShadowMap", SINSTANCE(CShadowRender)->GetTexture());	// �e�N�X�`�������Z�b�g
		m_pEffect->SetTexture("g_Texture", m_pImage->ppTex[i]);	// �e�N�X�`�������Z�b�g
		m_pEffect->SetTexture("g_normalMap", SINSTANCE(CImageManager)->Find2DImage(_T("image/normal.jpg"))->pTex);
		m_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B
		m_pImage->pMesh->DrawSubset(i);						// ���b�V����`��
	}
	m_pEffect->EndPass();
	m_pEffect->End();
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}