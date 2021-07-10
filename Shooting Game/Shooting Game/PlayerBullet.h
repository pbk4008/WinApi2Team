#pragma once
#ifndef __PLAYERBULLET_H__
#define __PLAYERBULLET_H__

#include "Obj.h"
class CPlayerBullet :
    public CObj
{
public:
	CPlayerBullet();
	~CPlayerBullet() override;

public:
	void Initialize() override;
	void LateInit() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;
};
#endif

