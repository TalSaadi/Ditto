#include "pch.h"
#include "Bitmap.hpp"


PBITMAPINFO Bitmap::create_bitmap_info_struct(HBITMAP bitmap_handle)
{
	BITMAP bitmap;

	// Retrieve the bitmap color format, width, and height.  
	if (!GetObjectW(bitmap_handle, sizeof(BITMAP), (LPSTR)&bitmap))
	{
		throw WindowsException();
	}

	uint16_t color_bits_counter = Bitmap::convert_color_format_to_bits_count(bitmap);

	PBITMAPINFO pbmi;

	if (color_bits_counter < 24)
	{
		size_t bytes = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << color_bits_counter);
		HLOCAL local = LocalAlloc(LPTR, bytes);
		pbmi = static_cast<PBITMAPINFO>(local);
	}
	else
	{
		pbmi = static_cast<PBITMAPINFO>(LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER)));
	}

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bitmap.bmWidth;
	pbmi->bmiHeader.biHeight = bitmap.bmHeight;
	pbmi->bmiHeader.biPlanes = bitmap.bmPlanes;
	pbmi->bmiHeader.biBitCount = bitmap.bmBitsPixel;

	if (color_bits_counter < 24)
	{
		pbmi->bmiHeader.biClrUsed = (1 << color_bits_counter);
	}

	pbmi->bmiHeader.biCompression = BI_RGB;

	uint32_t size = ((pbmi->bmiHeader.biWidth * color_bits_counter + 31) & ~31) / 8 * pbmi->bmiHeader.biHeight;
	
	pbmi->bmiHeader.biSizeImage = size;
	pbmi->bmiHeader.biClrImportant = 0;
	
	return pbmi;
}

uint16_t Bitmap::convert_color_format_to_bits_count(BITMAP bitmap)
{
	uint16_t color_bits_counter = static_cast<uint16_t>(bitmap.bmPlanes * bitmap.bmBitsPixel);

	if (color_bits_counter == 1)
		color_bits_counter = 1;
	else if (color_bits_counter <= 4)
		color_bits_counter = 4;
	else if (color_bits_counter <= 8)
		color_bits_counter = 8;
	else if (color_bits_counter <= 16)
		color_bits_counter = 16;
	else if (color_bits_counter <= 24)
		color_bits_counter = 24;
	else color_bits_counter = 32;

	return color_bits_counter;
}

void Bitmap::create_bitmap_file(const std::wstring& file_name, PBITMAPINFO bitmap_info, HBITMAP bitmap_handle, HDC dc_handle)
{
	PBITMAPINFOHEADER info_header;
	info_header = (PBITMAPINFOHEADER)bitmap_info;
	byte* memory = static_cast<byte*>(GlobalAlloc(GMEM_FIXED, info_header->biSizeImage));

	if (!memory)
	{
		throw WindowsException();
	}

	if (!GetDIBits(dc_handle, bitmap_handle, 0, static_cast<uint16_t>(info_header->biHeight), memory, bitmap_info, DIB_RGB_COLORS))
	{
		throw WindowsException();
	}

	File bitmap_file{file_name};

	BITMAPFILEHEADER header;
	header.bfType = 0x4d42;
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfSize = static_cast<uint32_t>(sizeof(BITMAPFILEHEADER) +
											info_header->biSize + info_header->biClrUsed
											* sizeof(RGBQUAD) + info_header->biSizeImage);

	header.bfOffBits = static_cast<uint32_t>(sizeof(BITMAPFILEHEADER) +
											 info_header->biSize + info_header->biClrUsed
										     * sizeof(RGBQUAD));

	bitmap_file.write(reinterpret_cast<byte*>(&header), sizeof(BITMAPFILEHEADER));
	bitmap_file.write(reinterpret_cast<byte*>(info_header), sizeof(BITMAPINFOHEADER) + info_header->biClrUsed * sizeof(RGBQUAD));

	uint32_t bytes_count = info_header->biSizeImage;

	bitmap_file.write(reinterpret_cast<byte*>(memory), bytes_count);

	GlobalFree(static_cast<HGLOBAL>(memory));
}