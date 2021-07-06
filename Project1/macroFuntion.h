#pragma once
#include "pch.h"

inline void RenderRect(HDC hdc, FRECT& box)
{
	MoveToEx(hdc, box.left, box.top, NULL);
	LineTo(hdc, box.right, box.top);
	LineTo(hdc, box.right, box.bottom);
	LineTo(hdc, box.left, box.bottom);
	LineTo(hdc, box.left, box.top);
}


inline FRECT GetBoxData(FRECT& box)
{
	return box;
}

