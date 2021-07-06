#pragma once

#include <Windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include "Mmsystem.h"
#include "Digitalv.h"
#include <conio.h>
#include "KeyManager.h"
#pragma comment(lib, "winmm.lib")

#define WINSIZE_X	1002
#define WINSIZE_Y	524
#define WINSTART_X	0
#define WINSTART_Y	0

typedef struct tagFRECT
{
	float left;
	float top;
	float right;
	float bottom;
}FRECT, * PFRECT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;