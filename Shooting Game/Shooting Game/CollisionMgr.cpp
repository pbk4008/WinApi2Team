#include "framework.h"
#include "CollisionMgr.h"
#include "Obj.h"

void CCollisionMgr::CollisionRect(OBJLIST& _Dst, OBJLIST& _Src)
{
	for (auto pDst : _Dst)
	{
		if (pDst->getDead())
			continue;
		for (auto pSrc : _Src)
		{
			if (pSrc->getDead())
				continue;
			if (RectCheck(pDst, pSrc))
			{
				pDst->setCollisionTarget(pSrc);
				pSrc->setCollisionTarget(pDst);
				return;
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(OBJLIST& _Dst, OBJLIST& _Src)
{
	for (auto pDst : _Dst)
	{
		if (pDst->getDead())
			continue;
		for (auto pSrc : _Src)
		{
			if (pSrc->getDead())
				continue;
			if (SphereCheck(pDst, pSrc))
			{
				pDst->setCollisionTarget(pSrc);
				pSrc->setCollisionTarget(pDst);
				return;
			}
		}
	}
}

bool CCollisionMgr::SphereCheck(CObj* _Dst, CObj* _Src)
{
	float fD = CMathMgr::getDist(_Dst,_Src);

	float fSumRadius = (_Dst->getInfo().iCX >> 1) + (_Src->getInfo().iCX >> 1);

	if (fD <= fSumRadius)
		return true;
	return false;
}

bool CCollisionMgr::RectCheck(CObj* _Dst, CObj* _Src)
{
	float fW = abs(CMathMgr::getWidth(_Dst, _Src));
	float fH = abs(CMathMgr::getHight(_Dst, _Src));

	float fSumW = (_Dst->getInfo().iCX>>1) + (_Src->getInfo().iCX>>1);
	float fSumH = (_Dst->getInfo().iCY>>1) + (_Src->getInfo().iCY>>1);

	if (fW <= fSumW && fH <= fSumH)
		return true;
	return false;
}
