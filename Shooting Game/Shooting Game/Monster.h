#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"

class CMonster :
    public CObj
{
public:
	explicit CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

};


#endif // !__MONSTER_H__



