#pragma once
#include "C2DImage.h"

class CTitleSelect :
	public C2DImage
{
public:
	CTitleSelect();
	~CTitleSelect();
	void Initialize()override;
	void Update()override;
	void Draw()override;
};