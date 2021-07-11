#pragma once
#ifndef __MATHMGR_H__
#define __MATHMGR_H__
class CMathMgr
{
public:
	static float getDist(CObj_Edit* _Dst, CObj_Edit* _Src);
	static float getWidth(CObj_Edit* _Dst, CObj_Edit* _Src);
	static float getHight(CObj_Edit* _Dst, CObj_Edit* _Src);
	static float getAngle(CObj_Edit* _Dst, CObj_Edit* _Src);
};
#endif

