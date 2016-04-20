#include "stdafx.h"
#include "Effect.h"
#include "GraphicsDevice.h"
CEffect* CEffect::m_instance = nullptr;

HRESULT CEffect::SetEffect(LPCSTR pFileName){

	int size = m_EffectFiles.size();
	// すでに使用するXファイルがあれば新しく読み込まない
	for (int idx = 0; idx < size; idx++){
		if (!strcmp(m_EffectFiles[idx]->pFileName,pFileName)){
			m_NowEffect = m_EffectFiles[idx]->Effect;
			return S_OK;
		}
	}

	LoadEffect(pFileName);

	return S_OK;
}

void CEffect::LoadEffect(LPCSTR pFileName){
	HRESULT hr;
	LPD3DXBUFFER compileErrorBuffer = nullptr;
	EFFECT_DATA Effect;
	Effect.pFileName = pFileName;
	// ID3DXEffectインタフェース生成
	hr = D3DXCreateEffectFromFile(graphicsDevice(), pFileName/*シェーダプログラムが書き込まれたファイル名*/,
		NULL, NULL, D3DXSHADER_DEBUG, NULL, &(Effect.Effect), &compileErrorBuffer/*エラー情報が入る*/);
	if (FAILED(hr)) {
		MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		//(SUCCEEDED(hr), "error");
	}
	m_NowEffect = Effect.Effect;
	m_EffectFiles.push_back(&Effect);
}
