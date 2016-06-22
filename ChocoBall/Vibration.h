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
	D3DXVECTOR3 m_VibrationAmount;	// �U����
	float m_VibrationTime;			// �U������
	float m_ReflectionTime;			// �������]����
private:
	D3DXVECTOR3* m_Target;			// �U��������I�u�W�F�N�g�̈ړ��ʂ��i�[
};

