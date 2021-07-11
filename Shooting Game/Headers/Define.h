#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__
#define EDITWINCX 1024
#define EDITWINCY 768
#define WINCX 900
#define WINCY 1200
#define PURE =0
#define SCENE_CHANGE 1
#define NO_SCENE 0
#define GAME_QUIT -1
#define PI 3.14159265f
#define SAFE_DELETE(p) if(p) {delete p; p= nullptr;}
#define DEGREE2RADIAN(angle) angle*PI/180.f
#define RADIAN2DEGREE(radian) radian*180.f/PI
#endif