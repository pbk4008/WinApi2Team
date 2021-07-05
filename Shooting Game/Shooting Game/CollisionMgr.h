#pragma once
#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__
class CObj;
class CCollisionMgr
{
public:
	static void CollisionRect(OBJLIST& _Dst, OBJLIST& _Src);
	static void CollisionSphere(OBJLIST& _Dst, OBJLIST& _Src);
	static bool SphereCheck(CObj* _Dst, CObj* _Src);
	static bool RectCheck(CObj* _Dst, CObj* _Src);
};
#endif

