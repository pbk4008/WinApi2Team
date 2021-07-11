#include "framework.h"
#include "CollisionMgr.h"
#include "Obj_Edit.h"

void CCollisionMgr::CollisionRect(list<CObj_Edit*>& _Dst, list<CObj_Edit*>& _Src)
{
	for (auto pDst : _Dst)
	{
		for (auto pSrc : _Src)
		{
			if (RectCheck(pDst, pSrc))
			{
				pDst->setCollisionTarget(pSrc);
				pSrc->setCollisionTarget(pDst);
				return;
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(list<CObj_Edit*>& _Dst, list<CObj_Edit*>& _Src)
{
	for (auto pDst : _Dst)
	{
		for (auto pSrc : _Src)
		{
			if (SphereCheck(pDst, pSrc))
			{
				pDst->setCollisionTarget(pSrc);
				pSrc->setCollisionTarget(pDst);
				return;
			}
		}
	}
}

bool CCollisionMgr::SphereCheck(CObj_Edit* _Dst, CObj_Edit* _Src)
{
	float fD = CMathMgr::getDist(_Dst,_Src);

	float fSumRadius = (_Dst->getInfo().iCX >> 1) + (_Src->getInfo().iCX >> 1);

	if (fD <= fSumRadius)
		return true;
	return false;
}

bool CCollisionMgr::RectCheck(CObj_Edit* _Dst, CObj_Edit* _Src)
{
	float fW = abs(CMathMgr::getWidth(_Dst, _Src));
	float fH = abs(CMathMgr::getHight(_Dst, _Src));

	float fSumW = (_Dst->getInfo().iCX>>1) + (_Src->getInfo().iCX>>1);
	float fSumH = (_Dst->getInfo().iCY>>1) + (_Src->getInfo().iCY>>1);

	if (fW <= fSumW && fH <= fSumH)
		return true;
	return false;
}
