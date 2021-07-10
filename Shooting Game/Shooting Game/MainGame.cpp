#include "framework.h"
#include "MainGame.h"
#include "StartScene.h"

CMainGame::CMainGame() : m_pSceneMgr(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC,WINCX,WINCY);
	m_hOldBitMap = (HBITMAP)SelectObject(m_MemDC,m_hBitMap);

	srand(unsigned(time(NULL)));

	if (!m_pSceneMgr)
		m_pSceneMgr = CSceneMgr::getInstance();	
	m_pSceneMgr->AddScene(CAbstractFactory<CStartScene>::CreateScene(SCENE::START));
}

void CMainGame::LateInit()
{
	m_pSceneMgr->LateInit();
}

void CMainGame::Update()
{
	m_pSceneMgr->Update();
}
void CMainGame::LateUpdate()
{
	m_pSceneMgr->LateUpdate();
}
void CMainGame::Render()
{
	Rectangle(m_MemDC,0, 0, WINCX, WINCY);
	m_pSceneMgr->Render(m_MemDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_MemDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	CSceneMgr::getInstance()->DestroyInstance();
	CObjMgr::getInstance()->DestroyInstance();

	SelectObject(m_MemDC, m_hOldBitMap);
	DeleteObject(m_hOldBitMap);
	DeleteDC(m_MemDC);

	ReleaseDC(g_hWnd, m_hDC);
}