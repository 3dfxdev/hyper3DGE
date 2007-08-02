//------------------------------------------------------------------------
//  Basic image storage
//------------------------------------------------------------------------
// 
//  Copyright (c) 2003-2007  The EDGE Team.
// 
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------

#ifndef __EPI_IMAGEDATA_H__
#define __EPI_IMAGEDATA_H__

#include "epi.h"
#include "types.h"

namespace epi
{

typedef enum
{
  IDF_NONE = 0,

  IDF_ExtPalette = (1 << 0),  // palette is external (do not free)
}
image_data_flags_e;


class image_data_c
{
public:
	short width;
	short height;

	// Bytes Per Pixel, determines image mode:
	// 1 = palettised
	// 3 = format is RGB
	// 4 = format is RGBA
	short bpp;

  short flags;

  // for image loading, these will be the actual image size
  short used_w;
  short used_h;

	u8_t *pixels;

  // TODO: color_c *palette;

public:
	image_data_c(int _w, int _h, int _bpp = 3);
	~image_data_c();

  void Clear(u8_t val = 0);

	inline u8_t *PixelAt(int x, int y) const
	{
		// Note: DOES NOT CHECK COORDS

		return pixels + (y * width + x) * bpp;
	}

	inline void CopyPixel(int sx, int sy, int dx, int dy)
	{
		u8_t *src  = PixelAt(sx, sy);
		u8_t *dest = PixelAt(dx, dy);

		for (int i = 0; i < bpp; i++)
			*dest++ = *src++;
	}

	void Whiten();
	// convert all RGB(A) pixels to a greyscale equivalent.
	
	void Shrink(int new_w, int new_h);
	// shrink an image to a smaller image.
	// The old size and the new size must be powers of two.
	// For RGB(A) images the pixel values are averaged.
	//
	// NOTE: Palettised images are not supported.

	void Grow(int new_w, int new_h);
	// scale the image up to a larger size.
	// The old size and the new size must be powers of two.

  void RemoveAlpha();
  // convert an RGBA image to RGB.  Partially transparent colors
  // (alpha < 255) are blended with black.
};


// IMAGE LOADING FLAGS

typedef enum
{
  IRF_NONE = 0,

  IRF_Round_POW2 = (1 << 0),  // convert width / height to powers of two
// IRF_Invert_Y   = (1 << 1),  // invert the image vertically
}
image_read_flags_e;


} // namespace epi

#endif  /* __EPI_IMAGEDATA_H__ */
