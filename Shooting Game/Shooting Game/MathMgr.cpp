#include "framework.h"
#include "MathMgr.h"
#include "Obj.h"
float CMathMgr::getDist(CObj* _Dst, CObj* _Src)
{
	float fW = getWidth(_Dst, _Src);
	float fH = getHight(_Dst, _Src);

	return sqrtf(fW*fW+fH*fH);
}

float CMathMgr::getWidth(CObj* _Dst, CObj* _Src)
{
	return _Dst->getInfo().fX - _Src->getInfo().fX;
}

float CMathMgr::getHight(CObj* _Dst, CObj* _Src)
{
	return _Dst->getInfo().fY - _Src->getInfo().fY;
}

float CMathMgr::getAngle(CObj* _Dst, CObj* _Src)
{
	float fW = getWidth(_Dst, _Src);
	float fD = getDist(_Dst, _Src);

	float fAngle = acos(fW / fD);

	if (_Dst->getInfo().fY > _Src->getInfo().fY)
		fAngle *= -1;

	return fAngle;
}
