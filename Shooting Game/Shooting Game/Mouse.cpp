#include "framework.h"
#include "Mouse.h"
#include "Button.h"
#include "StageScene.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.iCX = 10.f;
	m_tInfo.iCY = 10.f;
	m_bNotDestroy = true;
}

void CMouse::LateInit()
{
}

int CMouse::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tInfo.fX = float(pt.x);
	m_tInfo.fY = float(pt.y);

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_pCollisionTarget)
		{
			BUTTON::NAME eButton = dynamic_cast<CButton*>(m_pCollisionTarget)->getButtonName();
			switch (eButton)
			{
				case BUTTON::START:
					m_eScene = SCENE::STAGE1;
					CSceneMgr::getInstance()->setCurrentScene(SCENE::STAGE1);
					CSceneMgr::getInstance()->AddScene(CAbstractFactory<CStageScene>::CreateScene(SCENE::STAGE1));
					m_pCollisionTarget = nullptr;
					return EVENT::GAME_START;
				case BUTTON::QUIT:
					DestroyWindow(g_hWnd);
					break;
			}
		}
	}
	return EVENT::NOEVENT;
}

void CMouse::LateUpdate()
{
	RectUpdate();
}

void CMouse::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
}
