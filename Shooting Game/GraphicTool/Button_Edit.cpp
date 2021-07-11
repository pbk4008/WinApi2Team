#include "framework.h"
#include "Button_Edit.h"

CButton_Edit::CButton_Edit()
{
}

CButton_Edit::CButton_Edit(BUTTON::NAME _eName)
{
	setName(_eName);
}

CButton_Edit::~CButton_Edit()
{
	Release();
}

void CButton_Edit::Initialize()
{
	m_tInfo.iCX = 200;
	m_tInfo.iCY = 100;
}

int CButton_Edit::Update()
{
	RectUpdate();
	return EDIT_EVENT::NOEVENT;
}

void CButton_Edit::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CButton_Edit::Release()
{
}
