#pragma once
#ifndef __BUTTON_EDIT_H__
#define __BUTTON_EDIT_H__
#include "Obj_Edit.h"

class CButton_Edit :
    public CObj_Edit
{
private:
    BUTTON::NAME m_Button;
public:
    CButton_Edit();
    CButton_Edit(BUTTON::NAME _eName);
    ~CButton_Edit();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
private:
    inline void setName(BUTTON::NAME _eName) { m_Button = _eName; }
public:
    inline void setPos(float _x, float _y) { m_tInfo.fX=_x; m_tInfo.fY=_y; }
public:
    inline BUTTON::NAME getName() { return m_Button; }
    
};
#endif

