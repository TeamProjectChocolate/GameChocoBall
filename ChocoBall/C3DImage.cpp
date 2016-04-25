#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"

HRESULT C3DImage::SetImage(){
	IMAGE3D* Image = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (Image != nullptr){
		m_NumMaterials = Image->NumMaterials;
		m_pMeshMat = Image->pMat;
		m_pMeshTex = Image->ppTex;
		m_pMesh = Image->pMesh;
		return S_OK;
	}

	LoadXFile();
	return S_OK;
}

HRESULT C3DImage::ReSet(){
	IMAGE3D* Image = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (Image != nullptr){
		m_NumMaterials = Image->NumMaterials;
		m_pMeshMat = Image->pMat;
		m_pMeshTex = Image->ppTex;
		m_pMesh = Image->pMesh;
		return S_OK;
	}

	LoadXFile();
	return S_OK;
}

HRESULT C3DImage::LoadXFile(){
	DWORD i;

	// X�t�@�C�����[�h
	if (FAILED(D3DXLoadMeshFromX(m_pFileName, D3DXMESH_MANAGED, graphicsDevice(), NULL, &m_pMaterials, NULL, &m_NumMaterials, &m_pMesh))){		// X�t�@�C���ǂݎ��
		return E_FAIL;
	};

	// X�t�@�C���ɖ@�����Ȃ��ꍇ�́A�@������������
	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL)){
		ID3DXMesh* pTempMesh = NULL;
		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF() | D3DFVF_NORMAL, graphicsDevice(), &pTempMesh);
		D3DXComputeNormals(pTempMesh, NULL);
		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}

	// �}�e���A���A�e�N�X�`���̏���
	m_pMeshMat = new D3DMATERIAL9[m_NumMaterials];		// ���b�V�������m��
	m_pMeshTex = new LPDIRECT3DTEXTURE9[m_NumMaterials];		// �e�N�X�`�����m��

	D3DXMATERIAL* d3Mat = (D3DXMATERIAL*)m_pMaterials->GetBufferPointer();

	for (i = 0; i < m_NumMaterials; i++){
		m_pMeshMat[i] = d3Mat[i].MatD3D;		// �}�e���A�����Z�b�g
		m_pMeshMat[i].Ambient = m_pMeshMat[i].Diffuse;		// ����������

		m_pMeshTex[i] = NULL;		// �e�N�X�`��������
		if (d3Mat[i].pTextureFilename != NULL && lstrlen(d3Mat[i].pTextureFilename) > 0){		// �g�p���Ă���e�N�X�`��������Γǂݍ���

			if (FAILED(D3DXCreateTextureFromFile(graphicsDevice(), d3Mat[i].pTextureFilename, &m_pMeshTex[i]))){
				return E_FAIL;
			}
		}
	}

	SINSTANCE(CImageManager)->Add3D(m_pFileName, m_pMeshMat, m_pMeshTex, m_NumMaterials, m_pMesh);		// IMAGE���z��ɒǉ�
	m_pMaterials->Release();		// �}�e���A�������
	return S_OK;
}

void C3DImage::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/Effect00.hlsl"));	// �g�p����shader�t�@�C�����w��(�f�t�H���g)
}

void C3DImage::Draw(){
	SetUpTechnique();
	UINT numPass;
	m_pEffect->Begin(&numPass/*�e�N�j�b�N���ɒ�`����Ă���p�X�̐����ԋp�����*/, 0);
	m_pEffect->BeginPass(0);	//�p�X�̔ԍ����w�肵�Ăǂ̃p�X���g�p���邩�w��

	SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
	//�����ŌŒ�`��Ɠ����悤�ɁA���[�J�����W�ɐݒ肳�ꂽ���_�Q���f�o�C�X�ɓn���B�ʏ�Ɠ������@�B
	//	���b�V�����������A�}�e���A����e�N�X�`����ݒ�
	//DrawSubset()���Ăяo���ĕ`��

	// ���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	D3DXMatrixIdentity(&mWorld);	// �s�񏉊���

	D3DXMatrixRotationX(&m_rotation, m_transform.angle.x);
	D3DXMatrixMultiply(&mWorld, &mWorld, &m_rotation);

	D3DXMatrixRotationY(&m_rotation, m_transform.angle.y);
	D3DXMatrixMultiply(&mWorld, &mWorld, &m_rotation);

	D3DXMatrixRotationZ(&m_rotation, m_transform.angle.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &m_rotation);

	D3DXMatrixTranslation(&m_translation, m_transform.position.x, m_transform.position.y, m_transform.position.z/*-18.0f*/);
	D3DXMatrixMultiply(&mWorld, &mWorld, &m_translation);

	m_pEffect->SetMatrix("World"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &mWorld/*�ݒ肵�����s��ւ̃|�C���^*/);

	// ���_�t�H�[�}�b�g���Z�b�g
	(*graphicsDevice()).SetFVF(m_pMesh->GetFVF());

	DWORD i;

	for (i = 0; i < m_NumMaterials; i++){
		//(*graphicsDevice()).SetMaterial(&m_pMeshMat[i]);		// �}�e���A�������Z�b�g
		m_pEffect->SetTexture("g_Texture", m_pMeshTex[i]);	// �e�N�X�`�������Z�b�g
		m_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
		m_pMesh->DrawSubset(i);						// ���b�V����`��
	}
	m_pEffect->EndPass();
	m_pEffect->End();
}