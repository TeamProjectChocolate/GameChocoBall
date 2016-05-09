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
	CTitleCursor* m_cursor;	//カーソル。
};