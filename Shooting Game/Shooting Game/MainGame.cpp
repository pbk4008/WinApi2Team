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
	Rectangle(m_hDC,0, 0, WINCX, WINCY);
	m_pSceneMgr->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
}