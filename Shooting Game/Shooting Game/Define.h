#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__
#define WINCX 1024
#define WINCY 768
#define PURE =0
#define SCENE_CHANGE 1
#define NO_SCENE 0
#define GAME_QUIT -1
#define SAFE_DELETE(p) if(p) {delete p; p= nullptr;}
#endif