#pragma once
#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__
class CObj_Edit;
class CCollisionMgr
{
public:
	static void CollisionRect(list<CObj_Edit*>& _Dst, list<CObj_Edit*>& _Src);
	static void CollisionSphere(list<CObj_Edit*>& _Dst, list<CObj_Edit*>& _Src);
	static bool SphereCheck(CObj_Edit* _Dst, CObj_Edit* _Src);
	static bool RectCheck(CObj_Edit* _Dst, CObj_Edit* _Src);
};
#endif

