#include "stdafx.h"
#include "GamePad.h"


CGamePad::CGamePad()
{
}


CGamePad::~CGamePad()
{
}

BYTE CGamePad::IsTriggerDecsion(){ return false; }
BYTE CGamePad::IsPressDecision(){ return false; }
BYTE CGamePad::IsTriggerCancel(){ return false; }
BYTE CGamePad::IsPressCancel(){ return false; }
BYTE CGamePad::IsTriggerEscape(){ return false; }
BYTE CGamePad::IsPressEscape(){ return false; }
BYTE CGamePad::IsTriggerShift(){ return false; }
BYTE CGamePad::IsPressShift(){ return false; }
BYTE CGamePad::IsTriggerSpace(){ return false; }
BYTE CGamePad::IsPressSpace(){ return false; }
BYTE CGamePad::IsTriggerUp(){ return false; }
BYTE CGamePad::IsPressUp(){ return false; }
BYTE CGamePad::IsTriggerDown(){ return false; }
BYTE CGamePad::IsPressDown(){ return false; }
BYTE CGamePad::IsTriggerRight(){ return false; }
BYTE CGamePad::IsPressRight(){ return false; }
BYTE CGamePad::IsTriggerLeft(){ return false; }
BYTE CGamePad::IsPressLeft(){ return false; }