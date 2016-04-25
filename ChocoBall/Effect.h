#pragma once
#include "Infomation.h"

class CEffect
{
	SINGLETON_DECL(CEffect);
public:
	LPD3DXEFFECT SetEffect(LPCSTR);
	LPD3DXEFFECT LoadEffect(LPCSTR);
	LPD3DXEFFECT FindEffect(LPCSTR);
private:
	vector<EFFECT_DATA*> m_EffectFiles;
};

