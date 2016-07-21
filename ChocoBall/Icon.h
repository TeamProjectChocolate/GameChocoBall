#pragma once
#include "C2DImage.h"
class CIcon :
	public C2DImage
{
public:
	CIcon();
	~CIcon();
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
};

