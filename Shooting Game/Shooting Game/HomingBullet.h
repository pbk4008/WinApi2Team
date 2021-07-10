#pragma once

#ifndef __HOMINGBULLET_H__
#define __HOMINGBULLET_H__

#include "Obj.h"
class CHomingBullet :
    public CObj
{
public:
	CHomingBullet();
	~CHomingBullet() override;

public:
	void Initialize() override;
	void LateInit() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;
};

#endif
