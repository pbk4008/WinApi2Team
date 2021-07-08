#include"framework.h"
#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = (float)WINCX/2;
	m_tInfo.fY = 400.f;
	
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;
	m_fSpeed = 5.f;
}

void CPlayer::LateInit()
{
	
}

int CPlayer::Update()
{
	if (m_bDead)
		return EVENT::DEAD;

	if(GetAsyncKeyState(VK_LEFT) & 0x8000) // TODO HJ : 措阿急老锭 风飘2 加档 贸府 & keyMgr 积己
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_tInfo.fX += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_tInfo.fY -= m_fSpeed;
	}
	
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_tInfo.fY += m_fSpeed;
	}
	
	return EVENT::NOEVENT;
}

void CPlayer::LateUpdate()
{
	RectUpdate();
}

void CPlayer::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}
