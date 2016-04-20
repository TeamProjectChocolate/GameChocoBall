#pragma once
#include "DirectInput.h"

class CKeyBoard :
	public CDirectInput
{
public:
	CKeyBoard();
	~CKeyBoard();
	static BOOL CALLBACK EnumKeyBoardCallback(const LPCDIDEVICEINSTANCE pDIDInst, LPVOID pRef);
	HRESULT CreateInput(HWND, LPDIRECTINPUT8)override;
	void Update()override;	// キー情報更新
	BYTE KBGetPrs(const UINT KeyCode)const override;	// キー判定(押しっぱなし)
	BYTE KBGetTrg(const UINT KeyCode)const override;	// キー判定(押した瞬間)
private:
	vector<LPDIRECTINPUTDEVICE8> m_DIKBDevices;	// DirectInputキーボードデバイス(複数接続されることを考慮して配列で管理する)
	vector<DIDEVICEINSTANCE> m_InstPointer;	// DirectInputが自動生成するインスタンスへのポインターを格納する配列
	int m_DeviceCount;						// デバイスをいくつ生成できたか
	BYTE m_KBOldBuf[256];	// 一瞬前のキーボード情報
	BYTE m_KBNowBuf[256];	// 現在のキーボード情報
};

////グローバル関数を定義してどこかにある実体を返す(ここでいうとCKeyBoardクラスのインスタンスを返す)
//inline CKeyBoard& KeyBoard()
//{
//	extern CKeyBoard g_KeyboardDevice;
//	return g_KeyboardDevice;
//}
