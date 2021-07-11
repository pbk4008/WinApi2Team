#pragma once
#ifndef __MAINGRAPHIC_H__
#define __MAINGRAPHIC_H__
class MainGraphic
{
private:
	HDC m_hDC;
	HDC m_MemDC;
	HBITMAP m_hBit;
	HBITMAP m_hOldBit;
public:
	MainGraphic();
	~MainGraphic();
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
};
#endif

