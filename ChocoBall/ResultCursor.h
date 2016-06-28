#pragma once
#include "C2DImage.h"
#include "DirectInput.h"
#include "Audio.h"

class CResultCursor :
	public C2DImage
{
public:
	CResultCursor();
	~CResultCursor();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release();
	void SetAudio(CAudio* audio){
		m_pAudio = audio;
	}
private:
	CAudio* m_pAudio;
	CInterface*	m_pInput;
	float t;
	short dir;
	bool isup;
	bool isdown;
};