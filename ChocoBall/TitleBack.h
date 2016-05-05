#pragma once
#include "C2DImage.h"
#include "DirectInput.h"

class CTitleBack :
	public C2DImage
{
public:
	CTitleBack();
	~CTitleBack();
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	CDirectInput* m_Input = nullptr;
};