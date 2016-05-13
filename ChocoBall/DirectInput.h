#pragma once
#include "stdafx.h"

class CDirectInput{
public:
	CDirectInput(){
		m_Device = nullptr;
	};
	~CDirectInput(){
		SAFE_RELEASE(m_Device);
	}
	virtual HRESULT CreateInput(HWND, LPDIRECTINPUT8) = 0;
	HRESULT WINAPI CooperativeLevel(HWND, LPDIRECTINPUTDEVICE8);	// DirectInput排他制御設定処理
	virtual void Update() = 0;
	virtual BYTE IsTriggerDecsion();// 決定ボタンが押されたら
	virtual BYTE IsPressDecision();	// 決定ボタンが長押し
	virtual BYTE IsTriggerCancel();	// キャンセル、戻るボタンが押されたら
	virtual BYTE IsPressCancel();	// キャンセル、戻るボタンが長押し
	virtual BYTE IsTriggerEscape();	// エスケープボタンが押されたら
	virtual BYTE IsPressEscape();	// エスケープボタン長押し
	virtual BYTE IsTriggerShift();	// シフトキーが押されたら
	virtual BYTE IsPressShift();	// シフトキー長押し
	virtual BYTE IsTriggerSpace();	// スペースキーが押されたら
	virtual BYTE IsPressSpace();	// スペースキー長押し
	virtual BYTE IsTriggerUp();		// ↑が押されたら
	virtual BYTE IsPressUp();		// ↑が長押し
	virtual BYTE IsTriggerDown();	// ↓が押されたら
	virtual BYTE IsPressDown();		// ↓が長押し
	virtual BYTE IsTriggerRight();	// →が押されたら
	virtual BYTE IsPressRight();	// →が長押し
	virtual BYTE IsTriggerLeft();	// ←が押されたら
	virtual BYTE IsPressLeft();		// ←が長押し
protected:
	LPDIRECTINPUTDEVICE8 m_Device;
	virtual BYTE GetPrs(const UINT KeyCode)const = 0;	// キー判定(押しっぱなし)
	virtual BYTE GetTrg(const UINT KeyCode)const = 0;	// キー判定(押した瞬間)
};

//グローバル関数を定義してどこかにある実体を返す(ここでいうとDirectInputオブジェクトを返す)

