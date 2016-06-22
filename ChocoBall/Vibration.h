#pragma once
#include "stdafx.h"
#include "CourceDef.h"

class CVibration
{
public:
	CVibration();
	~CVibration();
	void Initialize();
	void Update();
	void ThisVibration(D3DXVECTOR3*,D3DXVECTOR3, float,float);
	bool GetIsVibration(){
		return m_IsVibration;
	}
private:
	D3DXVECTOR3 m_currentDir;
	bool m_IsVibration;
	float m_VibrationCounter;
	float m_ReflectionCounter;
	CCourceDef m_CourceDef;
public:
	D3DXVECTOR3 m_dir;
	D3DXVECTOR3 m_VibrationAmount;	// U“®—Ê
	float m_VibrationTime;			// U“®ŠÔ
	float m_ReflectionTime;			// Œü‚«”½“]ŠÔ
private:
	D3DXVECTOR3* m_Target;			// U“®‚³‚¹‚éƒIƒuƒWƒFƒNƒg‚ÌˆÚ“®—Ê‚ğŠi”[
};

