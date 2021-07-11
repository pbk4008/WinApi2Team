#pragma once
#ifndef __POSMGR_EDIG_H__
#define __POSMGR_EDIG_H__
class CLine;
class CPosMgr_Edit
{
private:
	static CPosMgr_Edit* m_pInstance;
	list<CLine*> m_PosList;
private:
	CPosMgr_Edit();
	~CPosMgr_Edit();
public:
	void Render(HDC _hDC);
	void Release();
public:
	static CPosMgr_Edit* getInstance();
	static void DestroyInstance();
public:
	inline void AddPos(CLine* _Line) { m_PosList.emplace_back(_Line); }
public:
	inline list<CLine*> getList() { return m_PosList; }
};
#endif

