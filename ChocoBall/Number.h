#pragma once
#include "C2DImage.h"
#include "stdafx.h"
#include "Number.h"

#define NUMBER_NUM 10

class CNumber :public C2DImage{
public:
	CNumber();
	~CNumber();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetValue(const int value){ m_value = value; };		// �O������󂯎�����l��m_value�Ɋi�[
	void AddValue(const int value){ m_value += value; };		// �O������󂯎�����l��m_value�ɉ��Z
private:
	int m_value;	// ���l
};