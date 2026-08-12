#include <utility>
#include <sstream>
#include <wincodec.h>
#include <string>
#include <Windows.h>

#include "FreeType.h"
#include "ft2build.h"
#include "DXTrace.h"
#include "BindableBase.h"

#include FT_FREETYPE_H

std::map<wchar_t, FreeType::Character> FreeType::mCharacters;

static std::string GetExeDirA()
{
	char path[MAX_PATH] = {};
	GetModuleFileNameA(nullptr, path, MAX_PATH);
	std::string full(path);
	const size_t pos = full.find_last_of("\\/");
	if (pos == std::string::npos)
	{
		return ".";
	}
	return full.substr(0, pos);
}

FreeType::FreeType(Graphics& gfx)
	: mFontSize(30)
{
}

void FreeType::setFontSize(unsigned int value)
{
	mFontSize = value;
}

FreeType::Character FreeType::getChar(Graphics& gfx, wchar_t key)
{
	auto it = mCharacters.find(key);
	if (it == mCharacters.end())
	{
		LoadChar(gfx, key);
		it = mCharacters.find(key);
		if (it == mCharacters.end())
		{
			Character empty{};
			return empty;
		}
	}
	return it->second;
}

void FreeType::LoadChar(Graphics& gfx, wchar_t wstr)
{
	FT_Library library = nullptr;
	if (FT_Init_FreeType(&library) != 0)
	{
		return;
	}

	FT_Face face = nullptr;
	const std::string fontPath = GetExeDirA() + "\\Resource\\Fonts\\msyh.ttc";
	if (FT_New_Face(library, fontPath.c_str(), 0, &face) != 0 || face == nullptr)
	{
		FT_Done_FreeType(library);
		return;
	}

	if (FT_Set_Pixel_Sizes(face, 0, mFontSize) != 0)
	{
		FT_Done_Face(face);
		FT_Done_FreeType(library);
		return;
	}

	if (FT_Load_Char(face, wstr, FT_LOAD_RENDER) != 0)
	{
		FT_Done_Face(face);
		FT_Done_FreeType(library);
		return;
	}

	FT_Bitmap bitmap = face->glyph->bitmap;

	if (wstr == L' ')
	{
		Character ch{};
		ch.SizeX = mFontSize;
		ch.SizeY = mFontSize;
		ch.BearingX = 0;
		ch.BearingY = 0;
		ch.Advance = face->glyph->advance.x;
		mCharacters.insert(std::pair<wchar_t, Character>(wstr, ch));

		FT_Done_Face(face);
		FT_Done_FreeType(library);
		return;
	}

	if (bitmap.width == 0 || bitmap.rows == 0 || bitmap.buffer == nullptr)
	{
		FT_Done_Face(face);
		FT_Done_FreeType(library);
		return;
	}

	Character ch{};
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

	mCharacters.insert(std::pair<wchar_t, Character>(wstr, ch));

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}