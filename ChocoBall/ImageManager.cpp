#include "stdafx.h"
#include "ImageManager.h"
#include "GraphicsDevice.h"

CImageManager* CImageManager::m_instance = nullptr;

void CImageManager::Add2D(IMAGE2D* image){
	// �V�����ǂݍ���X�t�@�C����o�^
	m_ImageList.push_back(image);		// IMAGE2D���z��ɒǉ�
}

IMAGE2D* CImageManager::LoadTextureFile(LPCSTR pFileName){
	IMAGE2D* image;
	image = new IMAGE2D;
	strcpy(image->pFileName,pFileName);

	D3DXIMAGE_INFO imgInfo;										//�摜���i�[�p�\����
	D3DXCreateTextureFromFileEx(graphicsDevice(), pFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0xff000000, &imgInfo, NULL, &image->pTex);	//�e�N�X�`���Ǎ�
	RECT rec = { 0, 0, imgInfo.Width, imgInfo.Height };			//�`��̈�
	image->RealSize.x = imgInfo.Width;
	image->RealSize.y = imgInfo.Height;
	IDirect3DSurface9* surface;
	image->pTex->GetSurfaceLevel(0, &surface);
	D3DSURFACE_DESC desc;
	surface->GetDesc(&desc);
	image->UnRealSize.x = desc.Width;
	image->UnRealSize.y = desc.Height;
	surface->Release();
	SINSTANCE(CImageManager)->Add2D(image);
	return image;
}

IMAGE2D* CImageManager::Find2DImage(LPCSTR pFileName){
	int size = m_ImageList.size();
	// ���łɎg�p����e�N�X�`���t�@�C��������΂����Ԃ�
	for (int idx = 0; idx < size; idx++){
		if (!strcmp(m_ImageList[idx]->pFileName,pFileName)){
			return m_ImageList[idx];
		}
	}
	return LoadTextureFile(pFileName);
}

void CImageManager::Add3D(LPCSTR pFileName,CSkinModelData* ModelData)
{
	// �V�����ǂݍ���X�t�@�C����o�^
	IMAGE3D* image;
	image = new IMAGE3D;
	strcpy(image->pFileName,pFileName);
	image->pModel = ModelData;
	m_ModelList.push_back(image);		// IMAGE3D���z��ɒǉ�
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

void CImageManager::DeleteAll(){
	for (int idx = 0,size = m_ModelList.size(); idx < size; idx++){
		SAFE_DELETE(m_ModelList[idx]->pModel);
	}
	m_ModelList.clear();
	for (int idx = 0, size = m_ImageList.size(); idx < size; idx++){
		SAFE_DELETE(m_ImageList[idx]->pTex);
		SAFE_DELETE(m_ImageList[idx]);
	}
	m_ImageList.clear();
}