#pragma once
#include "C2DImage.h"
#include "DirectInput.h"

class CResultCursor;

class CResultSelect :
	public C2DImage
{
public:
	CResultSelect();
	~CResultSelect();
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	CResultCursor* m_resultcursor;	//カーソル。
	CDirectInput* m_Input = nullptr;
	float t;
	short dir;
};