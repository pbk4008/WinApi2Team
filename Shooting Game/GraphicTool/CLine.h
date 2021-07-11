#pragma once
#ifndef __LINE_H__
#define __LINE_H__
class CLine
{
private:
	LINEINFO m_tInfo;
public:
	CLine();
	CLine(POS _tLPos, POS _tRPos);
	~CLine();
public:
	void Render(HDC _hDC);
	void Release();
public:
	inline const LINEINFO& getInfo()const { return m_tInfo; }
};
#endif

