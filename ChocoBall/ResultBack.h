#pragma once
#include "C2DImage.h"

class CResultBack :
	public C2DImage
{
public:
	CResultBack();
	~CResultBack();
	void Initialize()override;
	void Update()override;
	void Draw()override;
};