#include "stdafx.h"
#include "ImageManager.h"

CImageManager* CImageManager::m_instance = nullptr;

void CImageManager::Add2D(LPCSTR pFileName,LPDIRECT3DTEXTURE9 pTexture,RECT rect){
	// �V�����ǂݍ���X�t�@�C����o�^
	IMAGE2D* image;
	image = new IMAGE2D;
	image->pFileName = pFileName;
	image->pTex = pTexture;
	image->rect = rect;
	m_ImageList.push_back(image);		// IMAGE���z��ɒǉ�
}

IMAGE2D* CImageManager::Find2DImage(LPCSTR pFileName){
	int size = m_ImageList.size();
	// ���łɎg�p����e�N�X�`���t�@�C��������΂����Ԃ�
	for (int idx = 0; idx < size; idx++){
		if (!strcmp(m_ImageList[idx]->pFileName,pFileName)){
			return m_ImageList[idx];
		}
	}
	return nullptr;
}

void CImageManager::Add3D(LPCSTR pFileName, D3DMATERIAL9* m_pMeshMat,
	LPDIRECT3DTEXTURE9* m_pMeshTex,DWORD m_NumMaterials,LPD3DXMESH m_pMesh)
{
	// �V�����ǂݍ���X�t�@�C����o�^
	IMAGE3D* image;
	image = new IMAGE3D;
	image->pFileName = pFileName;
	image->ppTex = m_pMeshTex;
	image->pMat = m_pMeshMat;
	image->pMesh = m_pMesh;
	image->NumMaterials = m_NumMaterials;
	m_ModelList.push_back(image);		// IMAGE���z��ɒǉ�
}

IMAGE3D* CImageManager::Find3DImage(LPCSTR pFileName){
	int size = m_ModelList.size();
	// ���łɎg�p����X�t�@�C��������΂����Ԃ�
	for (int idx = 0; idx < size; idx++){
		if (!strcmp(m_ModelList[idx]->pFileName,pFileName)){
			return m_ModelList[idx];
		}
	}
	return nullptr;
}