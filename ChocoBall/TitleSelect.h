#pragma once
#include "C2DImage.h"
#include "DirectInput.h"

class CTitleCursor;

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
	CTitleCursor* m_cursor;	//�J�[�\���B
	//CDirectInput* m_Input = nullptr;
	CInterface*	m_pInput;
	float t;
	short dir;
};
