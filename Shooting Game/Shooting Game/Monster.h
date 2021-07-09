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

public: inline bool GetIsSpawn() { return m_bIsSpawn; }

public: inline void SetEnemy(ENEMY::TYPE _type) { m_eType = _type; }
public: inline void SetSpawn() { m_bIsSpawn = !m_bIsSpawn; }

public: void CreateMonBullet();

private: ENEMY::TYPE m_eType;
private: bool m_bIsSpawn;

};


#endif // !__MONSTER_H__



