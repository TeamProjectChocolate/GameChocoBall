#pragma once
#include "C2DImage.h"
#include "DirectInput.h"

class CTitleCursor :
	public C2DImage
{
public:
	CTitleCursor();
	~CTitleCursor();
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	CDirectInput* m_Input = nullptr;
	float t;
	short dir;
};