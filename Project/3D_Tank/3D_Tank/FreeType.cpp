#include <utility>
#include<sstream>
#include <wincodec.h>

#include "FreeType.h"
#include "ft2build.h"
#include "DXTrace.h"
#include "BindableBase.h"

#include FT_FREETYPE_H

std::map<wchar_t, FreeType::Character> FreeType::mCharacters;

FreeType::FreeType(Graphics& gfx)
	:mFontSize(30)
{
}

void FreeType::setFontSize(unsigned int value)
{
	mFontSize = value;
}

FreeType::Character FreeType::getChar(Graphics& gfx, wchar_t key)
{
	if (mCharacters.find(key) == mCharacters.end())
	{
		LoadChar(gfx, key);
	}
	return mCharacters[key];
}

void FreeType::LoadChar(Graphics& gfx, wchar_t wstr)
{
	FT_Library library;
	FT_Init_FreeType(&library);

	FT_Face face;
	FT_New_Face(library, "./Resource/Fonts/msyh.ttc", 0, &face);

	FT_Set_Pixel_Sizes(face, 0, mFontSize);

	// Load character glyph 

	if (FT_Load_Char(face, wstr, FT_LOAD_RENDER))
	{
		return;
	}

	// Generate texture
	FT_Bitmap bitmap = face->glyph->bitmap;

	if (wstr == L' ')
	{
		Character ch;
		ch.SizeX = mFontSize;
		ch.SizeY = mFontSize;
		ch.BearingX = 0;
		ch.BearingY = 0;
		ch.Advance = face->glyph->advance.x;
		mCharacters.insert(std::pair<wchar_t, Character>(wstr, ch));
		FT_Done_Face(face);
		return;
	}

	Character ch;
	ch.SizeX = bitmap.width;
	ch.SizeY = bitmap.rows;
	ch.BearingX = face->glyph->bitmap_left;
	ch.BearingY = face->glyph->bitmap_top;
	ch.Advance = face->glyph->advance.x;

	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = bitmap.width;
	texDesc.Height = bitmap.rows;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = bitmap.buffer;
	sd.SysMemPitch = bitmap.width * sizeof(unsigned char);
	sd.SysMemSlicePitch = bitmap.width * bitmap.rows * sizeof(unsigned char);
	HRD(gfx.getDevice()->CreateTexture2D(&texDesc, &sd, ch.Texture.GetAddressOf()));

	// Now store character for later use
	mCharacters.insert(std::pair<wchar_t, Character>(wstr, ch));

	FT_Done_Face(face);
}