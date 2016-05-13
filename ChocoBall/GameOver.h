#pragma once
#include "C2DImage.h"
class CGameOver :
	public C2DImage
{
public:
	CGameOver();
	~CGameOver();
	void Initialize()override;
	void Update()override;
	void Draw()override;
};