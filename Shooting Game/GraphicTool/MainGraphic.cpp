#include "framework.h"
#include "MainGraphic.h"

MainGraphic::MainGraphic()
{
}

MainGraphic::~MainGraphic()
{
	Release();
}

void MainGraphic::Initialize()
{
	m_hDC = GetDC(g_hWnd);
}

void MainGraphic::Update()
{
}

void MainGraphic::Render()
{
	Rectangle(m_hDC,0, 0, EDITWINCX, EDITWINCY);
	Rectangle(m_hDC,300, 150, 700, 550);
	
}

void MainGraphic::Release()
{
	ReleaseDC(g_hWnd,m_hDC);
}
