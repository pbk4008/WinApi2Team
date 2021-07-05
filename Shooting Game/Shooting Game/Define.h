#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__
#define WINCX 800
#define WINCY 600
#define PURE =0
#define SCENE_CHANGE 1
#define NO_SCENE 0
#define GAME_QUIT -1
#define SAFE_DELETE(p) if(p) {delete p; p= nullptr;}
#endif