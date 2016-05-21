#pragma once

#include "DirectInput.h"

class CAudio;

class CScene
{
public:
	CScene(){
		m_ManagerNewFlg = false;
		m_pAudio = nullptr;
		m_pInput = nullptr;
	};
	~CScene(){};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	inline void ActiveManagerNewFlg(){
		m_ManagerNewFlg = true;
	}
protected:
	CAudio* m_pAudio;
	CInterface* m_pInput;
private:
	bool m_ManagerNewFlg;	// ObjectManagerƒNƒ‰ƒX‚Ånew‚³‚ê‚½‚à‚Ì‚©”»’è‚·‚é•Ï”
};

