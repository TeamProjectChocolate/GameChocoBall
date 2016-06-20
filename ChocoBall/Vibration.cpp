#include "stdafx.h"
#include "Vibration.h"


CVibration::CVibration()
{
}


CVibration::~CVibration()
{
}

void CVibration::Initialize(){
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VibrationAmount = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VibrationTime = 0.0f;
	m_currentDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_IsVibration = false;
	m_ReflectionTime = 0.0f;
	m_VibrationCounter = 0.0f;
	m_ReflectionCounter = 0.0f;
}

void CVibration::Update(){
	if (m_IsVibration){
		if (m_VibrationCounter <= m_VibrationTime){
			m_ReflectionCounter += 1.0f / 60.0f;
			if (m_ReflectionCounter >= m_ReflectionTime){
				m_VibrationAmount *= -1.0f;
				m_ReflectionCounter = 0.0f;
			}
			m_dir.y = 0.0f;
			D3DXVec3Cross(&m_currentDir, &m_dir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			*m_Target += m_VibrationAmount.x * m_currentDir;
			m_Target->y += m_VibrationAmount.y;
			*m_Target += m_dir * m_VibrationAmount.z;
		}
		else{
			m_VibrationCounter = 0.0f;
			m_IsVibration = false;
			return;
		}
		m_VibrationCounter += 1.0f / 60.0f;	
	}
}