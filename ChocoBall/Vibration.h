#pragma once
#include "stdafx.h"

class CVibration
{
public:
	CVibration();
	~CVibration();
	void Initialize();
	void Update();
	void Activate(){
		m_IsVibration = true;
		m_VibrationCounter = 0.0f;
		m_ReflectionCounter = 0.0f;
	}
	void SetIsVibration(bool flg){
		m_IsVibration = flg;
	}
	bool GetIsVibration(){
		return m_IsVibration;
	}
	void SetTarget(D3DXVECTOR3* target){
		m_Target = target;
	}
private:
	D3DXVECTOR3 m_currentDir;
	bool m_IsVibration;
	float m_VibrationCounter;
	float m_ReflectionCounter;
public:
	D3DXVECTOR3 m_dir;
	D3DXVECTOR3 m_VibrationAmount;	// �U����
	float m_VibrationTime;			// �U������
	float m_ReflectionTime;			// �������]����
private:
	D3DXVECTOR3* m_Target;			// �U��������I�u�W�F�N�g�̈ړ��ʂ��i�[
};

