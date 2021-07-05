#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__
class CSceneMgr;
class CMainGame
{
private:
	HDC m_hDC;
	CSceneMgr* m_pSceneMgr;
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
};
#endif

