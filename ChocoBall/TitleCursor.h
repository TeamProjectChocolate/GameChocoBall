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
	void Move();
private:
	
	CInterface*	m_pInput;
	short dir;
};