#pragma once

enum FillMethod
{
	Horizontal = 0,
	Vertical = 1,
};

enum FillOrigin
{
	Left = 0,
	Right = 1,
	Top = 2,
	Bottom = 3,
};


struct FillType
{
	FillMethod Method;
	FillOrigin Origin;

	static FillType HL;
	static FillType HR;
	static FillType VT;
	static FillType VB;
};
