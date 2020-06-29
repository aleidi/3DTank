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

	void setFontSize(unsigned int value);
	Character getChar(Graphics& gfx, wchar_t key);

private:
	void LoadChar(Graphics& gfx, wchar_t wstr);

private:
	static std::map<wchar_t, Character> mCharacters;
	unsigned int mFontSize;

};