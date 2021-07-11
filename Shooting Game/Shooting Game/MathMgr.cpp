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

	float fAngle = acosf(fW / fD);
	

	//if (_Dst->getInfo().fY > _Src->getInfo().fY)
	//	fAngle *= -1;

	return fAngle;
}

int CMathMgr::getHorizontal(POSLIST& pList)
{
	int iMax=0;
	int iMin = 0;
	for (auto pPos : pList)
	{
		if (pPos->fX > iMax || iMax == 0)
			iMax = pPos->fX;
		if (pPos->fX < iMin || iMin == 0)
			iMin = pPos->fX;
	}
	return iMax-iMin;
}

int CMathMgr::getVertical(POSLIST& pList)
{
	int iMax = 0;
	int iMin = 0;
	for (auto pPos : pList)
	{
		if (pPos->fY > iMax || iMax == 0)
			iMax = pPos->fY;
		if (pPos->fY < iMin || iMin == 0)
			iMin = pPos->fY;
	}
	return iMax - iMin;
}
