#pragma once
#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__
class CSceneMgr
{
private:
	static CSceneMgr* m_pInstance;
	SCENE::TAG m_eCurrentScene;
	SCENEVEC m_SceneVector;
	bool m_bChange;
private:
	CSceneMgr();
	~CSceneMgr();
public:
	void LateInit();
	void Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();
public:
	static CSceneMgr* getInstance();
public:
	void DestroyInstance();
	void StartScene();
public:
	inline void AddScene(CScene* _Scene) { m_SceneVector.emplace_back(_Scene); }
	inline void setCurrentScene(SCENE::TAG _eCurrentScene) { m_eCurrentScene = _eCurrentScene; }
public:
	inline SCENE::TAG getCurrentScene() { return m_eCurrentScene; }

};
#endif

