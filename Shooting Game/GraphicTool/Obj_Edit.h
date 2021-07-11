#pragma once
#ifndef __OBJ_EDIT_H__
#define __OBJ_EDIT_H__
class CObj_Edit
{
protected:
	INFO m_tInfo;
	RECT m_tRect;
	CObj_Edit* m_pCollisonTarget;
public:
	CObj_Edit();
	virtual ~CObj_Edit();
public:
	virtual void Initialize()PURE;
	virtual int Update()PURE;
	virtual void Render(HDC _hDC)PURE;
	virtual void Release()PURE;
protected:
	void RectUpdate();
public:
	inline void setCollisionTarget(CObj_Edit* _pObj) { m_pCollisonTarget = _pObj; }
public:
	inline const INFO& getInfo() const { return m_tInfo; }
};
#endif

