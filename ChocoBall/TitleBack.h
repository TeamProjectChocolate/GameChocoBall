#pragma once
#include "C2DImage.h"

class CTitleBack :
	public C2DImage
{
public:
	CTitleBack();
	~CTitleBack();
	void Initialize()override;
	void Update()override;
	void Draw()override;
};