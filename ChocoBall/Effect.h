#pragma once
#include "Infomation.h"

class CEffect
{
	SINGLETON_DECL(CEffect);
public:
	HRESULT SetEffect(LPCSTR);
	void LoadEffect(LPCSTR);
	inline LPD3DXEFFECT GetEffect()
	{
		return m_NowEffect;
	}
private:
	vector<EFFECT_DATA*> m_EffectFiles;
	LPD3DXEFFECT m_NowEffect;		// 現在使用中のエフェクトファイル
};

