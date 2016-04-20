#pragma once
#include "stdafx.h"

class CDirectInput{
	SINGLETON_DECL(CDirectInput);
public:
	HRESULT WINAPI DI_Init(HWND);
	void Update();
	BYTE KBGetPrs(const UINT KeyCode)const;
	BYTE KBGetTrg(const UINT KeyCode)const;
};