#pragma once
#include "Graphics.h"

class FreeType
{
public:
	struct Character
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture;
		unsigned int SizeX;
		unsigned int SizeY;
		signed int BearingX;
		signed int BearingY;
		signed long Advance;
	};

	FreeType(Graphics& gfx);

	void SetFontSize(unsigned int value);
	Character getChar(Graphics& gfx, std::wstring key);

private:
	void LoadChar(Graphics& gfx, std::wstring wstr);

private:
	std::map<std::wstring, Character> mCharacters;
	unsigned int mFontSize;
};