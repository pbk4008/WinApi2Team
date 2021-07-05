#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__
namespace OBJ
{
	enum ID {PLAYER, BUTTON,MOUSE,BULLET,MONSTER,END};
}
namespace BUTTON
{
	enum NAME{START,QUIT,END};
}
namespace SCENE
{
	enum TAG{START,STAGE1,END};
}
namespace EVENT
{
	enum TRIGGER{DEAD, GAME_START, GAME_END, NOEVENT, END};
}
namespace SCENE_STATE
{
	enum STATE{NO,CHANGE,END};
}
#endif