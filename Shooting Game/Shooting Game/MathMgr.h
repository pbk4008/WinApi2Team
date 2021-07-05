#pragma once
#ifndef __MATHMGR_H__
#define __MATHMGR_H__
class CMathMgr
{
public:
	static float getDist(CObj* _Dst, CObj* _Src);
	static float getWidth(CObj* _Dst, CObj* _Src);
	static float getHight(CObj* _Dst, CObj* _Src);
	static float getAngle(CObj* _Dst, CObj* _Src);
};
#endif

