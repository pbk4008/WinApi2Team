#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__
typedef struct tagInfo
{
	float fX;
	float fY;
	int iCX;
	int iCY;
}INFO;
typedef struct tagPos
{
	float fX;
	float fY;
	tagPos()
	{}
	tagPos(float _x, float _y)
		:fX(_x), fY(_y)
	{

	}
}POS;
typedef struct tagLineInfo
{
	POS tLPos;
	POS tRPos;
	tagLineInfo()
	{
		ZeroMemory(&tLPos, sizeof(POS));
		ZeroMemory(&tRPos, sizeof(POS));
	}
	tagLineInfo(POS _tLPos, POS _tRPos)
		: tLPos(_tLPos),tRPos(_tRPos)
	{
		
	}
}LINEINFO;
typedef struct tagDis
{
	int iCX;
	int iCY;
	tagDis()
	{}
	tagDis(int _icx, int _icy)
		:iCX(_icx),iCY(_icy)
	{
	}
}DISINFO;
#endif