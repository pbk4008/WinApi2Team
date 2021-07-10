#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__
namespace OBJ//오브젝트 종류
{
	enum ID {BUTTON,BULLET,BOSSBULLET,MONBULLET,MONSTER,BOSS, PLAYER,MOUSE,END};
}
namespace BUTTON//버튼 종류
{
	enum NAME{START,QUIT,END};
}
namespace SCENE//씬 종류
{
	enum TAG{START,STAGE1,END};
}
namespace EVENT//이벤트 종류
{
	enum TRIGGER{DEAD, GAME_START, GAME_END, NOEVENT, END};
}
namespace SCENE_STATE//씬 상태
{
	enum STATE{NO,CHANGE,END};
}
namespace BOSS
{
	enum STAGE {STAGE1,STAGE_END};
	enum PATTERN {BASIC=0,PATTERN_1, PATTERN_2, PATTERN_3, PATTENR_END};
}

namespace ENEMY
{
	enum TYPE { ENEMY_1, ENEMY_2, ENEMY_3, TYPE_END };
	enum PATTERN { PATTERN_1, PATTERN_2 , PATTERN_END };
}

#endif