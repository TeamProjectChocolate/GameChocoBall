#pragma once

enum CollisionType{
	CollisionType_Player,			//プレイヤーのコリジョン。
	CollisionType_Map,				//地形コリジョン。
	CollisionType_Chocoball,		//チョコボール。
	CollisionType_ChocoballTrigger,	//チョコボール起動コリジョン。
};