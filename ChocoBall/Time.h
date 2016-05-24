#pragma once
#include "C2DImage.h"
#include "stdafx.h"
#include<time.h>


class CTime :public C2DImage{
public:
	CTime(){
		strcpy(m_pFileName, "image\\Number.png");

	}
	~CTime(){};
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetTime(int time)
	{
		m_time = time;
	}
private:
	float m_time;	// êîíl
};