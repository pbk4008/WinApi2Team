#pragma once
#ifndef __HPBAR_H__
#define __HPBAR_H__
#include "Obj.h"
class CHpBar :
    public CObj
{
public:
    CHpBar();
    virtual ~CHpBar();
public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
};
#endif

