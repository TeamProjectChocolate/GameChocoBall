#pragma once
#include "stdafx.h"

class CDirectInput{
public:
	CDirectInput();
	~CDirectInput(){
		SAFE_RELEASE(m_Device);
	}
	virtual HRESULT CreateInput(HWND, LPDIRECTINPUT8) = 0;
	HRESULT WINAPI CooperativeLevel(HWND, LPDIRECTINPUTDEVICE8);	// DirectInput排他制御設定処理
	virtual void Update() = 0;
	virtual BYTE KBGetPrs(const UINT KeyCode)const = 0;	// キー判定(押しっぱなし)
	virtual BYTE KBGetTrg(const UINT KeyCode)const = 0;	// キー判定(押した瞬間)
protected:
	LPDIRECTINPUTDEVICE8 m_Device;
};

//グローバル関数を定義してどこかにある実体を返す(ここでいうとDirectInputオブジェクトを返す)

