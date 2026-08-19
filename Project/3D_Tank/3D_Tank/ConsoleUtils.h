#pragma once

//------------------------------------------------------------------------
//
//  ファイル名: ConsoleUtils.h
//
//  概要: コンソール操作用のユーティリティ
//
//  作成者: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <windows.h>
#include <conio.h>
#include <iostream>

// デフォルトの文字色はwincon.hを参照
inline void SetTextColor(WORD colors)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, colors);
}

inline void PressAnyKeyToContinue()
{
	// 文字色を白に変更
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

	std::cout << "\n\nPress any key to continue" << std::endl;

	while (!_kbhit()) {}

	return;
}


