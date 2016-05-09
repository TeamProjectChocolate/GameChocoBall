#pragma once
#include "C2DImage.h"

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
	CDirectInput* m_Input;
	CTitleCursor* m_cursor;	//カーソル。
};