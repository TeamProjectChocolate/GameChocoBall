#pragma once
#include "C2DImage.h"
#include "stdafx.h"
#include<time.h>


class CTime :public C2DImage{
public:
	CTime(){
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
	int m_time;	// êîíl
};
