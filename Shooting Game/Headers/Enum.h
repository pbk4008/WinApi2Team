#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__
namespace OBJ//������Ʈ ����
{
	enum ID {BUTTON,BULLET,BOSSBULLET,MONBULLET, SCREWBULLET, HOMINGBULLET, MONSTER,BOSS, PLAYER,SHIELD, MOUSE, HPBAR,END};
}
namespace BUTTON//��ư ����
{
	enum NAME{START,QUIT,REMOVE,SAVE,END};
}
namespace SCENE//�� ����
{
	enum TAG{START,STAGE1,END};
}
namespace EVENT//�̺�Ʈ ����
{
	enum TRIGGER{DEAD, GAME_START, GAME_END, NOEVENT, END};
}
namespace SCENE_STATE//�� ����
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
namespace EDIT_OBJ
{
	enum ID {MOUSE,BUTTON,END};
}
namespace EDIT_EVENT
{
	enum EVENT{NODRAW,REMOVE,SAVE,NOEVENT};
}
#endif