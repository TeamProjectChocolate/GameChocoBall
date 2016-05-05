#pragma once
#include "stdafx.h"
#include "KeyBoard.h"

class CInputManager
{
	SINGLETON_DECL(CInputManager);
public:
	//DirectInputオブジェクト生成関数
	//引き数: なし
	//返り値: HRESULT型 エラーコードを返却
	//呼び出し例: SINSTANCE(CInputManager)->DI_Init();
	//※プログラム中で必ず最初に一回だけ呼び出してください
	HRESULT WINAPI DI_Init(); 

	//キーボードのDirectInputデバイスの生成関数
	//引き数: HWND型 ウィンドウハンドル
	//返り値: なし
	//呼び出し例: SINSTANCE(CInputManager)->CreateKeyBoard(g_hWnd);
	//※プログラム中で必ず最初に一回だけ呼び出してください
	void CreateKeyBoard(HWND hWnd);
	void Add(CDirectInput*);
	void SetCurrentInput(CDirectInput*);
	//void SelectInterface();
	CDirectInput* GetInput(){
		return m_currentInput;
	}
	void Update();
	void ReleaseObject();
private:
	LPDIRECTINPUT8 m_pInputObject = nullptr;	// DirectInputオブジェクト
	vector<CDirectInput*> m_Inputs;	// キーボードが複数あれば複数格納
	CDirectInput* m_currentInput= nullptr;

	//vectorに登録された要素をすべて削除する関数
	//※デストラクタにて呼び出される
	void DeleteAll();
};

