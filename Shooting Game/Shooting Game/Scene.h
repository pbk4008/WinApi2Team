#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__
class CObjMgr;
class CScene
{
protected:
	SCENE::TAG m_eTag;
	CObjMgr* m_ObjMgr;
public:
	CScene();
	virtual ~CScene();
public:
	virtual void Initialize()PURE;
	virtual void LateInit()PURE;
	virtual int Update()PURE;
	virtual void LateUpdate()PURE;
	virtual void Render(HDC _hDC)PURE;
	virtual void Release()PURE;
public:
	inline void setTag(SCENE::TAG _eTag) { m_eTag = _eTag; }
protected:
	virtual void CreateBackGround(HDC _hDC) PURE;
};
#endif

