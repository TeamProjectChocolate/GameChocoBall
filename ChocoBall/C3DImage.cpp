#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"


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

void C3DImage::SetUp(){
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

	SINSTANCE(CEffect)->GetEffect()->SetMatrix("World"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &mWorld/*�ݒ肵�����s��ւ̃|�C���^*/);
	//g_pEffect->SetTexture("g_Texture", texture /*�e�N�X�`�����*/);
	SINSTANCE(CEffect)->GetEffect()->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
}

void C3DImage::Draw(){

	DWORD i;

	// ���_�V�F�[�_���Z�b�g(�g��Ȃ��ꍇ��NULL)
	//(*graphicsDevice()).SetVertexShader(NULL);

	this->SetUp();

	// ���_�t�H�[�}�b�g���Z�b�g
	(*graphicsDevice()).SetFVF(m_pMesh->GetFVF());

	for (i = 0; i < m_NumMaterials; i++){
		//(*graphicsDevice()).SetMaterial(&m_pMeshMat[i]);		// �}�e���A�������Z�b�g
		SINSTANCE(CEffect)->GetEffect()->SetTexture("g_Texture", m_pMeshTex[i]);	// �e�N�X�`�������Z�b�g
		m_pMesh->DrawSubset(i);						// ���b�V����`��
	}
}