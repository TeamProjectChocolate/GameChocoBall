#pragma once
#include "C2DImage.h"
#include "DirectInput.h"
#include "Audio.h"

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
	void Release();
	void SetAudio(CAudio* audio){
		m_pAudio = audio;
	}
private:
	CAudio* m_pAudio;
	CInterface*	m_pInput;
	short dir;
};