#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__
#include "Obj.h"
class CMouse :
    public CObj
{
public:
    CMouse();
    virtual ~CMouse();
public:
    // CObj을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
};
#endif

