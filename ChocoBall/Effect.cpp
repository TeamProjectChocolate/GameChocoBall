#include "stdafx.h"
#include "Effect.h"
#include "GraphicsDevice.h"
#include "Assert.h"


CEffect* CEffect::m_instance = nullptr;

LPD3DXEFFECT CEffect::SetEffect(LPCSTR pFileName){
	int size = m_EffectFiles.size();
	// ���łɎg�p����V�F�[�_�[�t�@�C��������ΐV�����ǂݍ��܂Ȃ�
	for (int idx = 0; idx < size; idx++){
		if (!strcmp(m_EffectFiles[idx]->pFileName,pFileName)){
			return m_EffectFiles[idx]->Effect;
		}
	}
	return LoadEffect(pFileName);
}

LPD3DXEFFECT CEffect::LoadEffect(LPCSTR pFileName){
	HRESULT hr;
	LPD3DXBUFFER compileErrorBuffer = nullptr;
	EFFECT_DATA* Effect = new EFFECT_DATA;
	CH_ASSERT(strlen(pFileName) < MAX_FILENAME);
	strcpy(Effect->pFileName,pFileName);
	// ID3DXEffect�C���^�t�F�[�X����
	hr = D3DXCreateEffectFromFile(graphicsDevice(), pFileName/*�V�F�[�_�v���O�������������܂ꂽ�t�@�C����*/,
		NULL, NULL, D3DXSHADER_SKIPVALIDATION, NULL, &(Effect->Effect), &compileErrorBuffer/*�G���[��񂪓���*/);
	if (FAILED(hr)) {
		MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		abort();
		return nullptr;
		//(SUCCEEDED(hr), "error");
	}
	m_EffectFiles.push_back(Effect);
	return Effect->Effect;
}

LPD3DXEFFECT CEffect::FindEffect(LPCSTR name)
{
	int size = m_EffectFiles.size();
	for (int idx = 0; idx < size; idx++){
		if (!strcmp(m_EffectFiles[idx]->pFileName, name)){
			return m_EffectFiles[idx]->Effect;
		}
	}
	return nullptr;
}

void CEffect::DeleteAll(){
	for (int idx = 0,size = m_EffectFiles.size(); idx < size; idx++){
		SAFE_DELETE(m_EffectFiles[idx]->Effect);
		SAFE_DELETE(m_EffectFiles[idx]);
	}
	m_EffectFiles.clear();
}


