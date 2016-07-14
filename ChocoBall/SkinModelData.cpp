#include "stdafx.h"
#include "SkinModelData.h"
#include "GraphicsDevice.h"
#include "AllocateHierarchy.h"
#include "Assert.h"


CSkinModelData::CSkinModelData()
{
}


CSkinModelData::~CSkinModelData()
{
	SAFE_RELEASE(m_pAnimController);
}

void CSkinModelData::LoadModelData(LPCSTR pFileName,CAnimation* anim){
	CAllocateHierarchy alloc;

	// ���f���f�[�^���[�h
	HRESULT hr = 
		D3DXLoadMeshHierarchyFromX(
		pFileName,
		D3DXMESH_VB_MANAGED,
		graphicsDevice(),
		&alloc,
		nullptr,
		&m_frameRoot,
		&m_pAnimController
		);

	CH_ASSERT(!FAILED(hr));
	SetUpBoneMatrixPointers(m_frameRoot, m_frameRoot);
	if (m_pAnimController != nullptr){
		anim->Initialize(m_pAnimController);
	}
}

void CSkinModelData::SetUpBoneMatrixPointers(LPD3DXFRAME pFrame, LPD3DXFRAME pRootFrame /*�c���[�\���̂����Ƃ����̃m�[�h���g�p����̂œn���Ă���*/){
	// �{�[���̃c���[�\���̂����ꂩ�̃m�[�h�������Ă��郁�b�V������T��

	if (pFrame->pMeshContainer != nullptr){
		// ���b�V����񂪂���΂����(�s��)����֐����Ăяo��
		SetUpBoneMatrixPointersOnMesh(pFrame->pMeshContainer, pRootFrame);
	}
	// �m�[�h�ɌZ�킪����ΒT���𑱍s����
	if (pFrame->pFrameSibling != nullptr){
		SetUpBoneMatrixPointers(pFrame->pFrameSibling, pRootFrame);
	}
	// �m�[�h�Ɏq������ΒT���𑱍s����
	if (pFrame->pFrameFirstChild != nullptr){
		SetUpBoneMatrixPointers(pFrame->pFrameFirstChild, pRootFrame);
	}
}

void CSkinModelData::SetUpBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME rootFrame){
	unsigned int iBone, cBones;
	D3DXFRAME_DERIVED* pFrame;
	m_pMeshContainer = static_cast<D3DXMESHCONTAINER_DERIVED*>(pMeshContainerBase);

	if (m_pMeshContainer->pSkinInfo != nullptr){
		cBones = m_pMeshContainer->pSkinInfo->GetNumBones();
		m_pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
		if (m_pMeshContainer->ppBoneMatrixPtrs == nullptr){
			return;
		}

		for (iBone = 0; iBone < cBones; iBone++){
			pFrame = static_cast<D3DXFRAME_DERIVED*>(D3DXFrameFind(rootFrame,
			m_pMeshContainer->pSkinInfo->GetBoneName(iBone)));
			if (pFrame == nullptr){
				return;
			}
			m_pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
		}
	}
}

void CSkinModelData::UpdateBoneMatrix(const D3DXMATRIX* matWorld){
	UpdateFrameMatrices(m_frameRoot, matWorld);
}

void CSkinModelData::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, const D3DXMATRIX* pParentMatrix)
{
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

	if (pParentMatrix != NULL)
		// �{�[���̃��[���h�ϊ�?
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	else
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;

	if (pFrame->pFrameSibling != NULL)
	{
		// �{�[���ɌZ�킪����΂�����X�V
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		// �{�[���Ɏq��������΂�����X�V
		UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}
