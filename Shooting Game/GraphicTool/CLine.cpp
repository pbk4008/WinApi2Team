#include "framework.h"
#include "CLine.h"

CLine::CLine()
{
	ZeroMemory(&m_tInfo, sizeof(LINEINFO));
}

CLine::CLine(POS _tLPos, POS _tRPos)
	:m_tInfo(_tLPos,_tRPos)
{
}

CLine::~CLine()
{
	Release();
}

void CLine::Render(HDC _hDC)
{
	MoveToEx(_hDC,m_tInfo.tLPos.fX, m_tInfo.tLPos.fY,nullptr);
	LineTo(_hDC, m_tInfo.tRPos.fX, m_tInfo.tRPos.fY);
}
void CLine::Release()
{
}
