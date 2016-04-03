//----------------------------------------------------------------------------
//  EDGE2 OGG Music Player (HEADER)
//----------------------------------------------------------------------------
// 
//  Copyright (c) 2004-2009  The EDGE2 Team.
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
//----------------------------------------------------------------------------
//
// -ACB- 2004/08/18 Written
//
#ifndef __OGGPLAYER_H__
#define __OGGPLAYER_H__

#include "i_defs.h"

#ifdef WIN32
//#include <C:\hyperedge\edge2\lib_win32\libvorbis-1.3.2\include\vorbis\vorbisfile.h>
#include <Vorbis/vorbisfile.h>
#endif

#include "../epi/sound_data.h"

class pl_entry_c;

/* FUNCTIONS */

abstract_music_c * S_PlayOGGMusic(const pl_entry_c *musdat, float volume, bool looping);

bool S_LoadOGGSound(epi::sound_data_c *buf, const byte *data, int length);

#endif  /* __OGGPLAYER_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
