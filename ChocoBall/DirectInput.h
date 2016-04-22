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
	virtual bool IsTriggerDecsion();// 決定ボタンが押されたら
	virtual bool IsPressDecision();	// 決定ボタンが長押し
	virtual bool IsTriggerCancel();	// キャンセル、戻るボタンが押されたら
	virtual bool IsPressCancel();	// キャンセル、戻るボタンが長押し
	virtual bool IsTriggerUp();		// ↑が押されたら
	virtual bool IsPressUp();		// ↑が長押し
	virtual bool IsTriggerDown();	// ↓が押されたら
	virtual bool IsPressDown();		// ↓が長押し
	virtual bool IsTriggerRight();	// →が押されたら
	virtual bool IsPressRight();	// →が長押し
	virtual bool IsTriggerLeft();	// ←が押されたら
	virtual bool IsPressLeft();		// ←が長押し
protected:
	LPDIRECTINPUTDEVICE8 m_Device;
	virtual BYTE GetPrs(const UINT KeyCode)const = 0;	// キー判定(押しっぱなし)
	virtual BYTE GetTrg(const UINT KeyCode)const = 0;	// キー判定(押した瞬間)
};

//グローバル関数を定義してどこかにある実体を返す(ここでいうとDirectInputオブジェクトを返す)

