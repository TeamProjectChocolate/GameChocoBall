#pragma once
#include "C2DImage.h"
#include "DirectInput.h"

class CTitleSelect :
	public C2DImage
{
public:
	CTitleSelect();
	~CTitleSelect();
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	CDirectInput* m_Input;
};