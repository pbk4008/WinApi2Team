#pragma once
#ifndef __OBJMGR_EDIT_H__
#define __OBJMGR_EDIT_H__
class CObj_Edit;
class CObjMgr_Edit
{
private:
	static CObjMgr_Edit* m_pInstance;
	list<CObj_Edit*> m_ObjList[EDIT_OBJ::END];
private:
	CObjMgr_Edit();
	~CObjMgr_Edit();
public:
	static CObjMgr_Edit* getInstance();
	static void DestroyInstance();
public:
	void Update();
	void Render(HDC _hDC);
	void Release();
public:
	void Save_Point();
public:
	inline void AddObj(EDIT_OBJ::ID _eID, CObj_Edit* _pObj) { m_ObjList[_eID].emplace_back(_pObj); }
public:
	inline list<CObj_Edit*>* getList(EDIT_OBJ::ID _eID) { return &m_ObjList[_eID]; }

};
#endif

