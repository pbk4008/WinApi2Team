#pragma once

#ifndef __SCREWBULLET_H__
#define __SCREWBULLET_H__

#include "Obj.h"
class CScrewBullet :
    public CObj
{
public:
	CScrewBullet();
	~CScrewBullet() override;

public:
	void Initialize() override;
	void LateInit() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;

private:
	POINT m_tCenterPos;
	float m_fCenterAngle;
	float m_fCenterSpeed;

	float m_fDis;

	bool m_bStart;
};

#endif
