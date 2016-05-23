#include "stdafx.h"
#include "Result.h"

CResult::CResult(){
	m_Text.Initialize();
	m_Over.Initialize();
	SetAlive(true);
}

CResult::~CResult(){

}

void CResult::Initialize(){
	// 今回はここには何も書きこまない
}

void CResult::Update(){
	m_Text.Update();
	m_Over.Update();
}

void CResult::Draw(){
	m_Text.Draw();
	m_Over.Draw();
}
