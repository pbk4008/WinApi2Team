#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"
class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer() override;

public:
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	CObj* Create_ScrewBullet();
	CObj* Create_HomingBullet();
	void Create_Bullet();
	void Create_Shield();


private:
	list<CObj*>* m_pBullet;
	int m_shieldCount;
	DWORD dwTime;
};

#endif
