#pragma once
#include "C2DImage.h"
#include "DirectInput.h"

class CResultCursor :
	public C2DImage
{
public:
	CResultCursor();
	~CResultCursor();
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	CInterface* m_Input = nullptr;
	float t;
	short dir;
};