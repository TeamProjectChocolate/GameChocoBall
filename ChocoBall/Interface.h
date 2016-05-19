#pragma once

#include "stdafx.h"

typedef enum INTERFACE_TYPE{ KEYBOARD = 0,GAMEPAD };

class CInterface
{
public:
	CInterface();
	~CInterface();
	virtual void Update() = 0;
	INTERFACE_TYPE GetType(){
		return m_InputType;
	}
	void SetType(INTERFACE_TYPE type){
		m_InputType = type;
	}
	virtual bool GetConnected() = 0;

	virtual BYTE IsTriggerDecsion() = 0;// 決定ボタンが押されたら
	virtual BYTE IsPressDecision() = 0;	// 決定ボタンが長押し
	virtual BYTE IsTriggerCancel() = 0;	// キャンセル、戻るボタンが押されたら
	virtual BYTE IsPressCancel() = 0;	// キャンセル、戻るボタンが長押し
	virtual BYTE IsTriggerEscape() = 0;	// エスケープボタンが押されたら
	virtual BYTE IsPressEscape() = 0;	// エスケープボタン長押し
	virtual BYTE IsTriggerShift() = 0;	// シフトキーが押されたら
	virtual BYTE IsPressShift() = 0;	// シフトキー長押し
	virtual BYTE IsTriggerSpace() = 0;	// スペースキーが押されたら
	virtual BYTE IsPressSpace() = 0;	// スペースキー長押し
	virtual BYTE IsTriggerUp() = 0;		// ↑が押されたら
	virtual BYTE IsPressUp() = 0;		// ↑が長押し
	virtual BYTE IsTriggerDown() = 0;	// ↓が押されたら
	virtual BYTE IsPressDown() = 0;		// ↓が長押し
	virtual BYTE IsTriggerRight() = 0;	// →が押されたら
	virtual BYTE IsPressRight() = 0;	// →が長押し
	virtual BYTE IsTriggerLeft() = 0;	// ←が押されたら
	virtual BYTE IsPressLeft() = 0;		// ←が長押し
private:
	INTERFACE_TYPE m_InputType;
};

