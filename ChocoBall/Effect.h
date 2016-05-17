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
	//vector�ɓo�^���ꂽ�v�f�����ׂč폜����֐�
	//���f�X�g���N�^�ɂČĂяo�����
	void DeleteAll();
};

