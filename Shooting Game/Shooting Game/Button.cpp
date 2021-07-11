#include "framework.h"
#include "Button.h"

CButton::CButton()
{
	ZeroMemory(m_szText, sizeof(m_szText));
}

CButton::~CButton()
{
	Release();
}

void CButton::Initialize()
{
	m_tInfo.iCX = 200;
	m_tInfo.iCY = 100;
}

void CButton::LateInit()
{
	switch (m_eName)
	{
	case BUTTON::START:
		swprintf_s(m_szText, L"시작하기");
		break;
	case BUTTON::QUIT:
		swprintf_s(m_szText, L"종료하기");
		break;
	}

}

int CButton::Update()
{
	return EVENT::NOEVENT;
}

void CButton::LateUpdate()
{
	RectUpdate();
}

void CButton::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	TextOut(_hDC, m_tInfo.fX-35, m_tInfo.fY, m_szText, lstrlen(m_szText));
}

void CButton::Release()
{
	SAFE_DELETE_ARR(m_PolygonList);
	SAFE_DELETE_ARR(m_iPosDisArr);
}
