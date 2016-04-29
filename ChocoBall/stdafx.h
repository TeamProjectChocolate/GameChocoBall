// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: プログラムに必要な追加ヘッダーをここで参照してください。

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include "d3d9.h"
#include "d3dx9.h"
#include "dinput.h"
#include <string>
#include <iostream>
#include <vector>
#include <list>

#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }	//インスタンスリリース
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p) = NULL; } }	//インスタンス配列削除
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p) = NULL; } }	//インスタンス削除

using namespace std;

#define SINGLETON_DECL(CLASS_NAME)				\
private:										\
	CLASS_NAME(){}								\
	~CLASS_NAME(){	DeleteAll();	}				\
	static CLASS_NAME* m_instance;				\
public:											\
	static CLASS_NAME*	GetInstance()			\
	{											\
		return m_instance;						\
	}											\
	static CLASS_NAME*	CreateInstance()		\
	{											\
		if (m_instance == NULL){				\
			m_instance = new CLASS_NAME();			\
		}											\
		return m_instance;						\
	}

#define SINSTANCE(CLASS_NAME) CLASS_NAME::GetInstance()		// シングルトンオブジェクトのインスタンスを取得するマクロ関数(引き数：クラス名)

#define CLASS_NAME(p) typeid(p).name()		//クラス名の文字列を取得するマクロ関数(引数：クラス名)