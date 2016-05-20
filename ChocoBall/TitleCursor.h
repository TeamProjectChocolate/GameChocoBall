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
	CInterface* m_Input = nullptr;
	short dir;
};