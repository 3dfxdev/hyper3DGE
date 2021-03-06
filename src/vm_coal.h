//------------------------------------------------------------------------
//  COAL General Stuff
//------------------------------------------------------------------------
//
//  Copyright (c) 2006-2009  The EDGE2 Team.
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

#ifndef __VM_COAL_H__
#define __VM_COAL_H__

#include "con_main.h"
#include "coal/coal.h"

void VM_InitCoal();
void VM_QuitCoal();

void VM_LoadCoalFire(const char *filename);
void VM_LoadLumpOfCoal(int lump);
void VM_LoadScripts();

void VM_RegisterHUD(coal::vm_c *vm);
void VM_RegisterPlaysim(coal::vm_c *vm);

// HUD stuff
void VM_BeginLevel(void);
void VM_RunHud(int split);

#endif // __VM_COAL_H__

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
