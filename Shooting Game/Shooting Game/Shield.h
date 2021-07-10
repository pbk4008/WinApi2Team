#pragma once
#ifndef __SHIELD_H__
#define __SHIELD_H__

#include "Obj.h"
class CShield : public CObj
{
public:
	CShield();
	~CShield() override;

public:
	void Initialize() override;
	void LateInit() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;

private:
	float m_fDis;
};

#endif
