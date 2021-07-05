#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__
class CObj
{
protected:
	INFO m_tInfo;
	RECT m_tRect;
	CObj* m_pCollisionTarget;
	bool m_bNotDestroy;
	bool m_bDead;
	SCENE::TAG m_eScene;
public:
	CObj();
	virtual ~CObj();
public:
	virtual void Initialize() PURE;
	virtual void LateInit() PURE;
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;
protected:
	void RectUpdate();
public:
	inline void setScene(SCENE::TAG _eTag) { m_eScene = _eTag; }
	inline void setPos(float _x, float _y) { m_tInfo.fX = _x, m_tInfo.fY = _y; }
	inline void setNotDestory() {	m_bNotDestroy = true; }
	inline void setDead(bool _bDead) { m_bDead = _bDead; }
	inline void setCollisionTarget(CObj* _pTarget) { m_pCollisionTarget = _pTarget; }
public:
	inline SCENE::TAG getScene() { return m_eScene; }
	inline bool getNotDestory() { return m_bNotDestroy; }
	inline bool getDead() { return m_bDead; }
	inline const INFO getInfo()const { return m_tInfo; }
};
#endif

