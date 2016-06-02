#pragma once
#include "C2DImage.h"
class CClearText :
	public C2DImage
{
public:
	CClearText();
	~CClearText();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	bool GetIsEnd(){
		return m_IsEnd;
	}
private:
	bool m_IsEnd;
	float t;
	short dir;

};
