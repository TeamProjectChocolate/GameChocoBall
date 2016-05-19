#pragma once
#include "C2DImage.h"
#include "stdafx.h"


class CTime :public C2DImage{
public:
	CTime(){
		strcpy(m_pFileName, "image\\Number.png");

	}
	~CTime(){};
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	int m_time;	// êîíl
};