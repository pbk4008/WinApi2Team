#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__
namespace OBJ//������Ʈ ����
{
	enum ID {PLAYER, BUTTON,MOUSE,BULLET,MONSTER,BOSS,BOSSBULLET, END};
}
namespace BUTTON//��ư ����
{
	enum NAME{START,QUIT,END};
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
#endif