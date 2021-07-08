#pragma once
#ifndef __OBJMGR_H__
#define __OBJMGR_H__
class CObjMgr
{
private:
	static CObjMgr* m_pInstance;
	OBJLIST m_ObjList[OBJ::END];
private:
	CObjMgr();
	~CObjMgr();
public:
	void LateInit();
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();
public:
	static CObjMgr* getInstance();
public:
	void DestroyInstance();
	void SceneObjectRemove(SCENE::TAG _eTag);
	CObj* ObjPooling(OBJ::ID _eID);
	CObj* DeadCheck(OBJ::ID _eID);
public:
	inline void AddObject(OBJ::ID _eID, CObj* pObj) { m_ObjList[_eID].emplace_back(pObj); }
	inline CObj* getPlayer() { return m_ObjList[OBJ::PLAYER].back(); }
	inline CObj* getObj(OBJ::ID _eID) { return m_ObjList[_eID].back(); }
	inline OBJLIST& getList(OBJ::ID _eID) { return m_ObjList[_eID]; }
};
#endif

