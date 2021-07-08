#pragma once
#ifndef __BOSSBULLET_H__
#define __BOSSBULLET_H__
#include "Obj.h"
class CBoss;
class CBossBullet :
    public CObj
{
private:
    BOSS::PATTERN m_ePattern;
public:
    CBossBullet();
    virtual ~CBossBullet();
public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
public:
    inline void setPattern(BOSS::PATTERN _ePattern) { m_ePattern = _ePattern; }
};
#endif

