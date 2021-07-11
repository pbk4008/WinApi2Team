#pragma once
#ifndef __MOUSE_EDIT_H__
#define __MOUSE_EDIT_H__
#include "Obj_Edit.h"

class CMouse_Edit :
    public CObj_Edit
{
private:
    RECT m_tBoard;
    bool m_bDrawCheck;
    bool m_bDrawFirstCheck;
    POS m_tPos[2];
public:
    CMouse_Edit();
    virtual ~CMouse_Edit();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
private:
    bool moveCheck();
    void Draw();
public:
    inline void setBoard(RECT _Board) { m_tBoard = _Board; }


};
#endif

