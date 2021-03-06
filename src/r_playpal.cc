//----------------------------------------------------------------------------
//  Wolfenstein, Blake Stone, ROTT Palette Generation
//----------------------------------------------------------------------------
// 
//  Copyright (c) Isotope SoftWorks / Andrew Apted
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

/* THOUGHTS:

Since this generates a PLAYPAL lump, this will need to be called
very early on in e_main when Wolf3D datas are detected, so 3DGE
knows how to load the PLAYPAL in. */

#include "system/i_defs.h"
#include "system/i_defs_gl.h"
#include "dm_state.h"
#include "r_texgl.h"

#include "games/wolf3d/wlf_local.h"

GLuint wlf_pal;
GLuint rott_pal;

const byte wolf_palette[256*3] =
{
	  0,  0,  0,   0,  0,170,   0,170,  0,   0,170,170, 170,  0,  0,
	170,  0,170, 170, 85,  0, 170,170,170,  85, 85, 85,  85, 85,255,
	 85,255, 85,  85,255,255, 255, 85, 85, 255, 85,255, 255,255, 85,
	255,255,255, 239,239,239, 223,223,223, 211,211,211, 195,195,195,
	182,182,182, 170,170,170, 154,154,154, 142,142,142, 125,125,125,
	113,113,113, 101,101,101,  85, 85, 85,  73, 73, 73,  56, 56, 56,
	 44, 44, 44,  32, 32, 32, 255,  0,  0, 239,  0,  0, 227,  0,  0,
	215,  0,  0, 203,  0,  0, 190,  0,  0, 178,  0,  0, 166,  0,  0,
	154,  0,  0, 138,  0,  0, 125,  0,  0, 113,  0,  0, 101,  0,  0,
	 89,  0,  0,  77,  0,  0,  65,  0,  0, 255,219,219, 255,186,186,
	255,158,158, 255,125,125, 255, 93, 93, 255, 65, 65, 255, 32, 32,
	255,  0,  0, 255,170, 93, 255,154, 65, 255,138, 32, 255,121,  0,
	231,109,  0, 207, 97,  0, 182, 85,  0, 158, 77,  0, 255,255,219,
	255,255,186, 255,255,158, 255,255,125, 255,251, 93, 255,247, 65,
	255,247, 32, 255,247,  0, 231,219,  0, 207,199,  0, 182,174,  0,
	158,158,  0, 134,134,  0, 113,109,  0,  89, 85,  0,  65, 65,  0,
	211,255, 93, 199,255, 65, 182,255, 32, 162,255,  0, 146,231,  0,
	130,207,  0, 117,182,  0,  97,158,  0, 219,255,219, 190,255,186,
	158,255,158, 130,255,125,  97,255, 93,  65,255, 65,  32,255, 32,
	  0,255,  0,   0,255,  0,   0,239,  0,   0,227,  0,   0,215,  0,
	  4,203,  0,   4,190,  0,   4,178,  0,   4,166,  0,   4,154,  0,
	  4,138,  0,   4,125,  0,   4,113,  0,   4,101,  0,   4, 89,  0,
	  4, 77,  0,   4, 65,  0, 219,255,255, 186,255,255, 158,255,255,
	125,255,251,  93,255,255,  65,255,255,  32,255,255,   0,255,255,
	  0,231,231,   0,207,207,   0,182,182,   0,158,158,   0,134,134,
	  0,113,113,   0, 89, 89,   0, 65, 65,  93,190,255,  65,178,255,
	 32,170,255,   0,158,255,   0,142,231,   0,125,207,   0,109,182,
	  0, 93,158, 219,219,255, 186,190,255, 158,158,255, 125,130,255,
	 93, 97,255,  65, 65,255,  32, 36,255,   0,  4,255,   0,  0,255,
	  0,  0,239,   0,  0,227,   0,  0,215,   0,  0,203,   0,  0,190,
	  0,  0,178,   0,  0,166,   0,  0,154,   0,  0,138,   0,  0,125,
	  0,  0,113,   0,  0,101,   0,  0, 89,   0,  0, 77,   0,  0, 65,
	 40, 40, 40, 255,227, 52, 255,215, 36, 255,207, 24, 255,195,  8,
	255,182,  0, 182, 32,255, 170,  0,255, 154,  0,231, 130,  0,207,
	117,  0,182,  97,  0,158,  81,  0,134,  69,  0,113,  52,  0, 89,
	 40,  0, 65, 255,219,255, 255,186,255, 255,158,255, 255,125,255,
	255, 93,255, 255, 65,255, 255, 32,255, 255,  0,255, 227,  0,231,
	203,  0,207, 182,  0,182, 158,  0,158, 134,  0,134, 109,  0,113,
	 89,  0, 89,  65,  0, 65, 255,235,223, 255,227,211, 255,219,199,
	255,215,190, 255,207,178, 255,199,166, 255,190,158, 255,186,146,
	255,178,130, 255,166,113, 255,158, 97, 243,150, 93, 235,142, 89,
	223,138, 85, 211,130, 81, 203,125, 77, 190,121, 73, 182,113, 69,
	170,105, 65, 162,101, 60, 158, 97, 56, 146, 93, 52, 138, 89, 48,
	130, 81, 44, 117, 77, 40, 109, 73, 36,  93, 65, 32,  85, 60, 28,
	 73, 56, 24,  65, 48, 24,  56, 44, 20,  40, 32, 12,  97,  0,101,
	  0,101,101,   0, 97, 97,   0,  0, 28,   0,  0, 44,  48, 36, 16,
	 73,  0, 73,  81,  0, 81,   0,  0, 52,  28, 28, 28,  77, 77, 77,
	 93, 93, 93,  65, 65, 65,  48, 48, 48,  52, 52, 52, 219,247,247,
	186,235,235, 158,223,223, 117,203,203,  73,195,195,  32,182,182,
	 32,178,178,   0,166,166,   0,154,154,   0,142,142,   0,134,134,
	  0,125,125,   0,121,121,   0,117,117,   0,113,113,   0,109,109,
	154,  0,138
};

// mostly the same as the Wolfenstein-3D palette (a couple changes).
const byte spear_palette[256*3] =
{
	  0,  0,  0,   0,  0,170,   0,170,  0,   0,170,170, 170,  0,  0,
	170,  0,170, 170, 85,  0, 170,170,170,  85, 85, 85,  85, 85,255,
	 85,255, 85,  85,255,255, 255, 85, 85, 255, 85,255, 255,255, 85,
	255,255,255, 239,239,239, 223,223,223, 211,211,211, 195,195,195,
	182,182,182, 170,170,170, 154,154,154, 142,142,142, 125,125,125,
	113,113,113, 101,101,101,  85, 85, 85,  73, 73, 73,  56, 56, 56,
	 44, 44, 44,  32, 32, 32, 255,  0,  0, 239,  0,  0, 227,  0,  0,
	215,  0,  0, 203,  0,  0, 190,  0,  0, 178,  0,  0, 166,  0,  0,
	154,  0,  0, 138,  0,  0, 125,  0,  0, 113,  0,  0, 101,  0,  0,
	 89,  0,  0,  77,  0,  0,  65,  0,  0, 255,219,219, 255,186,186,
	255,158,158, 255,125,125, 255, 93, 93, 255, 65, 65, 255, 32, 32,
	255,  0,  0, 255,170, 93, 255,154, 65, 255,138, 32, 255,121,  0,
	231,109,  0, 207, 97,  0, 182, 85,  0, 158, 77,  0, 255,255,219,
	255,255,186, 255,255,158, 255,255,125, 255,251, 93, 255,247, 65,
	255,247, 32, 255,247,  0, 231,219,  0, 207,199,  0, 182,174,  0,
	158,158,  0, 134,134,  0, 113,109,  0,  89, 85,  0,  65, 65,  0,
	211,255, 93, 199,255, 65, 182,255, 32, 162,255,  0, 146,231,  0,
	130,207,  0, 117,182,  0,  97,158,  0, 219,255,219, 190,255,186,
	158,255,158, 130,255,125,  97,255, 93,  65,255, 65,  32,255, 32,
	  0,255,  0,   0,255,  0,   0,239,  0,   0,227,  0,   0,215,  0,
	  4,203,  0,   4,190,  0,   4,178,  0,   4,166,  0,   4,154,  0,
	  4,138,  0,   4,125,  0,   4,113,  0,   4,101,  0,   4, 89,  0,
	  4, 77,  0,   4, 65,  0, 219,255,255, 186,255,255, 158,255,255,
	125,255,251,  93,255,255,  65,255,255,  32,255,255,   0,255,255,
	  0,231,231,   0,207,207,   0,182,182,   0,158,158,   0,134,134,
	  0,113,113,   0, 89, 89,   0, 65, 65,  93,190,255,  65,178,255,
	 32,170,255,   0,158,255,   0,142,231,   0,125,207,   0,109,182,
	  0, 93,158, 219,219,255, 186,190,255, 158,158,255, 125,130,255,
	 93, 97,255,  65, 65,255,  32, 36,255,   0,  4,255,   0,  0,255,
	  0,  0,239,   0,  0,227,   0,  0,215,   0,  0,203,   0,  0,190,
	  0,  0,178,   0,  0,166,   0,  0,154,   0,  0,138,   0,  0,125,
	  0,  0,113,   0,  0,101,   0,  0, 89,   0,  0, 77,   0,  0, 65,
	 40, 40, 40, 255,227, 52, 255,215, 36, 255,207, 24, 255,195,  8,
	255,182,  0,   0, 56,  0,   0, 40,  0, 154,  0,231, 130,  0,207, /* <-- */
	117,  0,182,  97,  0,158,  81,  0,134,  69,  0,113,  52,  0, 89,
	 40,  0, 65, 255,219,255, 255,186,255, 255,158,255, 255,125,255,
	255, 93,255, 255, 65,255, 255, 32,255, 255,  0,255, 227,  0,231,
	203,  0,207, 182,  0,182, 158,  0,158, 134,  0,134, 109,  0,113,
	 89,  0, 89,  65,  0, 65, 255,235,223, 255,227,211, 255,219,199,
	255,215,190, 255,207,178, 255,199,166, 255,190,158, 255,186,146,
	255,178,130, 255,166,113, 255,158, 97, 243,150, 93, 235,142, 89,
	223,138, 85, 211,130, 81, 203,125, 77, 190,121, 73, 182,113, 69,
	170,105, 65, 162,101, 60, 158, 97, 56, 146, 93, 52, 138, 89, 48,
	130, 81, 44, 117, 77, 40, 109, 73, 36,  93, 65, 32,  85, 60, 28,
	 73, 56, 24,  65, 48, 24,  56, 44, 20,  40, 32, 12,  97,  0,101,
	  0,101,101,   0, 97, 97,   0,  0, 28,   0,  0, 44,  48, 36, 16,
	 73,  0, 73,  81,  0, 81,   0,  0, 52,  28, 28, 28,  77, 77, 77,
	 93, 93, 93,  65, 65, 65,  48, 48, 48,  52, 52, 52, 219,247,247,
	186,235,235, 158,223,223, 117,203,203,  73,195,195,  32,182,182,
	 32,178,178,   0,166,166,   0,154,154,   0,142,142,   0,134,134,
	  0,125,125,   0,121,121,   0,117,117,   0,113,113,   0,109,109,
	154,  0,138
};

const byte blake_palette[256*3] =
{
	  0,  0,  0,   4,  4,  4,  12, 12, 12,  20, 20, 20,  28, 28, 28,
	 36, 36, 36,  44, 44, 44,  52, 52, 52,  60, 60, 60,  69, 69, 69,
	 77, 77, 77,  85, 85, 85,  93, 93, 93, 101,101,101, 109,109,109,
	117,117,117,  32,  0,  0,  52,  0,  0,  73,  0,  0,  93,  0,  0,
	113,  4,  4, 134,  4,  4, 154,  8,  8, 174, 12, 12, 195, 16, 16,
	199, 36, 36, 207, 56, 56, 211, 81, 81, 219,101,101, 223,125,125,
	231,154,154, 239,182,182,  44, 20,  0,  60, 28,  0,  81, 36,  0,
	101, 48,  0, 117, 56,  4, 138, 69,  4, 154, 77,  8, 174, 89, 12,
	195,101, 16, 199,113, 36, 207,130, 56, 211,146, 81, 219,158,101,
	223,174,125, 231,195,154, 239,211,182,  44, 44,  0,  60, 60,  0,
	 81, 81,  0, 101,101,  0, 117,121,  4, 134,138,  8, 150,154, 12,
	166,170, 20, 182,186, 28, 199,203, 36, 207,207, 56, 211,215, 81,
	219,219,105, 227,227,130, 231,231,158, 239,239,186,  12, 20,  0,
	 32, 44,  0,  52, 69,  0,  69, 93,  0,  89,117,  0, 109,142,  0,
	125,166,  0, 146,190,  0, 154,195, 16, 166,203, 40, 178,211, 65,
	190,219, 93, 203,227,121, 215,231,154, 227,239,182, 239,247,219,
	  0, 20,  0,   0, 44,  0,   0, 69,  0,   0, 93,  0,   0,117,  0,
	  0,142,  0,   0,166,  0,   0,195,  0,  16,199, 16,  40,207, 40,
	 69,215, 69,  93,219, 93, 121,227,121, 154,235,154, 186,239,186,
	219,247,219,   0, 20, 12,   0, 44, 28,   0, 69, 40,   0, 93, 56,
	  0,117, 73,   4,142, 89,   4,166,105,   4,190,121,  24,195,134,
	 48,203,146,  73,211,158,  97,219,174, 125,227,190, 158,231,203,
	186,239,219, 219,247,235,   0, 20, 20,   0, 44, 44,   0, 69, 69,
	  0, 93, 93,   0,117,117,   0,142,142,   0,166,166,   0,190,190,
	 16,195,195,  40,203,203,  65,211,211,  93,219,219, 121,227,227,
	154,231,231, 182,239,239, 219,247,247,   0, 20, 44,   0, 28, 60,
	  0, 40, 81,   0, 48,101,   4, 60,117,   4, 69,138,   8, 81,154,
	 12, 93,174,  16,105,195,  36,117,199,  56,134,207,  81,146,211,
	101,162,219, 125,174,223, 154,195,231, 182,211,239,   0,  0, 44,
	  0,  0, 60,   0,  0, 81,   0,  0,101,   4,  4,117,   4,  4,138,
	  8,  8,154,  12, 12,174,  16, 16,195,  40, 40,203,  65, 65,211,
	 93, 93,219, 121,121,227, 154,154,231, 182,182,239, 219,219,247,
	117,117,117, 125,125,125, 134,134,134, 142,142,142, 154,154,154,
	162,162,162, 170,170,170, 178,178,178, 190,190,190, 199,199,199,
	207,207,207, 219,219,219, 227,227,227, 235,235,235, 243,243,243,
	255,255,255,  60, 24,  0,  65, 28,  0,  73, 32,  4,  81, 40,  4,
	 85, 44,  8,  93, 52, 12,  97, 56, 20, 105, 65, 24, 113, 73, 32,
	203,207, 40, 203,178, 36, 203,146, 32, 199,113, 28, 199, 81, 24,
	195, 48, 20, 195, 16, 16,  44,  0, 20,  60,  0, 28,  81,  0, 36,
	101,  0, 48, 117,  4, 56, 138,  4, 69, 154,  8, 77, 174, 12, 89,
	195, 16,101, 199, 36,113, 207, 56,130, 211, 81,146, 219,101,158,
	223,125,174, 231,154,195, 239,182,211,  32, 20,  8,  48, 28, 12,
	 65, 40, 16,  81, 52, 24,  97, 65, 28, 113, 73, 32, 130, 85, 36,
	150, 97, 44, 162,109, 60, 170,121, 77, 178,134, 89, 190,146,109,
	199,162,130, 211,178,150, 219,190,170, 231,211,195,   8, 20, 32,
	 12, 28, 48,  20, 40, 65,  24, 52, 81,  32, 65, 97,  36, 73,113,
	 44, 85,130,  52, 97,146,  60,109,162,  77,121,170,  89,134,178,
	109,146,190, 130,162,199, 150,178,211, 170,190,219, 195,211,231,
	 28, 28, 32, 251,251,255,  97,  0,  0, 251,  0,  0,   0, 48,  0,
	  0,251,  0,  28, 32, 28, 117,121,117, 251,255,251, 117,121,117,
	 40, 40,207, 121,121,231, 219,231,251, 121,121,231,  40, 40,207,
	154,  0,138
};

const byte Rott_Doom_Pal_Converter[] = {
1,4,134,146,148,75,76,151,78,79,1,1,2,7,8,0,

80,85,90,94,97,99,102,3,107,109,110,111,5,6,6,7,

8,8,0,0,0,48,17,21,25,28,31,35,37,182,183,183,

184,185,186,188,189,46,47,47,47,47,8,0,0,0,0,0,

225,227,228,229,230,230,231,231,231,221,221,232,167,167,167,12,

12,12,12,0,0,84,114,119,123,125,127,12,12,0,0,0,

157,159,9,9,10,10,127,127,8,0,0,0,219,220,220,166,

//166,39,40,41,44,44,45,46,47,47,8,80,85,128,130,x
32,34,36,38,40,42,44,46, 47,47,8,80,85,128,130,

133,136,139,141,13,14,110,5,1,2,8,8,0,0,0,89,

91,93,95,97,98,100,102,103,3,106,107,108,109,111,5,6,

6,244,245,245,246,246,246,246,0,53,18,128,130,255,255,137,

138,141,142,14,15,238,238,1,2,2,2,8,8,0,0,0,

37,41,44,47,47,47,0,210,55,58,61,64,67,68,70,71,

73,73,74,76,76,77,238,238,239,239,239,239,239,2,2,2,

2,2,2,8,8,0,0,0,0,0,4,50,211,161,162,162,

162,215,217,220,221,233,235,235,41,228,231,221,234,189,47,254

};


const byte rott_palette[256*3] =
{
		0, 0, 0 ,
	252, 252, 252 ,
	192, 184, 160 ,
	176, 168, 132 ,
	160, 152, 108 ,
	148, 140, 88 ,
	136, 128, 84 ,
	124, 120, 80 ,
	116, 108, 76 ,
	104, 96, 72 ,
	92, 88, 68 ,
	80, 76, 60 ,
	72, 68, 56 ,
	60, 56, 40 ,
	48, 44, 28 ,
	36, 32, 20 ,
	248, 248, 248 ,
	228, 228, 228 ,
	208, 208, 208 ,
	192, 192, 192 ,
	180, 180, 180 ,
	168, 168, 168 ,
	152, 152, 152 ,
	140, 140, 140 ,
	124, 124, 124 ,
	112, 112, 112 ,
	100, 100, 100 ,
	92, 92, 92 ,
	84, 84, 84 ,
	72, 72, 72 ,
	64, 64, 64 ,
	56, 56, 56 ,
	44, 44, 44 ,
	36, 36, 36 ,
	28, 28, 28 ,
	20, 20, 20 ,
	12, 12, 12 ,
	252, 240, 240 ,
	244, 212, 212 ,
	240, 184, 184 ,
	236, 160, 160 ,
	232, 136, 136 ,
	228, 116, 116 ,
	220, 92, 92 ,
	216, 68, 68 ,
	212, 48, 48 ,
	208, 28, 28 ,
	204, 12, 12 ,
	200, 0, 0 ,
	188, 0, 0 ,
	176, 0, 0 ,
	164, 0, 0 ,
	152, 0, 0 ,
	136, 0, 0 ,
	124, 0, 0 ,
	112, 0, 0 ,
	100, 0, 0 ,
	88, 0, 0 ,
	76, 12, 16 ,
	64, 0, 0 ,
	52, 0, 0 ,
	40, 0, 0 ,
	28, 0, 0 ,
	20, 0, 0 ,
	252, 252, 236 ,
	252, 252, 200 ,
	252, 252, 168 ,
	252, 252, 132 ,
	252, 252, 100 ,
	252, 252, 64 ,
	252, 252, 32 ,
	244, 236, 0 ,
	224, 220, 0 ,
	208, 200, 0 ,
	188, 184, 0 ,
	172, 168, 0 ,
	152, 152, 0 ,
	136, 132, 0 ,
	116, 116, 0 ,
	100, 100, 0 ,
	80, 80, 0 ,
	64, 64, 0 ,
	48, 48, 0 ,
	28, 28, 0 ,
	12, 12, 0 ,
	220, 252, 220 ,
	164, 224, 164 ,
	116, 196, 116 ,
	76, 172, 76 ,
	44, 144, 44 ,
	20, 120, 20 ,
	4, 96, 4 ,
	0, 80, 0 ,
	0, 64, 0 ,
	0, 48, 0 ,
	0, 32, 0 ,
	136, 152, 104 ,
	124, 136, 96 ,
	112, 124, 88 ,
	100, 108, 80 ,
	88, 96, 72 ,
	64, 80, 48 ,
	48, 64, 32 ,
	28, 52, 16 ,
	12, 36, 4 ,
	4, 20, 0 ,
	0, 8, 0 ,
	252, 156, 48 ,
	236, 144, 48 ,
	224, 132, 48 ,
	212, 120, 52 ,
	200, 108, 52 ,
	188, 100, 52 ,
	176, 92, 52 ,
	164, 80, 48 ,
	152, 72, 48 ,
	136, 64, 48 ,
	124, 60, 44 ,
	112, 52, 40 ,
	100, 44, 40 ,
	88, 40, 36 ,
	76, 32, 32 ,
	64, 28, 28 ,
	252, 248, 244 ,
	236, 228, 224 ,
	224, 212, 204 ,
	212, 192, 188 ,
	200, 172, 168 ,
	188, 152, 156 ,
	172, 136, 144 ,
	160, 124, 132 ,
	148, 108, 124 ,
	136, 96, 116 ,
	120, 80, 96 ,
	108, 68, 80 ,
	92, 60, 64 ,
	80, 48, 48 ,
	64, 40, 36 ,
	52, 32, 28 ,
	40, 24, 20 ,
	24, 16, 12 ,
	12, 8, 4 ,
	208, 212, 224 ,
	200, 204, 216 ,
	188, 192, 208 ,
	180, 184, 200 ,
	172, 176, 192 ,
	164, 168, 184 ,
	156, 160, 180 ,
	144, 148, 172 ,
	136, 140, 164 ,
	128, 136, 156 ,
	120, 124, 148 ,
	112, 120, 140 ,
	104, 112, 132 ,
	100, 104, 128 ,
	84, 88, 120 ,
	72, 76, 112 ,
	60, 64, 104 ,
	48, 56, 96 ,
	40, 44, 88 ,
	32, 36, 80 ,
	24, 28, 72 ,
	16, 20, 64 ,
	8, 12, 56 ,
	4, 8, 48 ,
	4, 4, 40 ,
	0, 0, 36 ,
	0, 0, 28 ,
	248, 220, 208 ,
	236, 208, 200 ,
	228, 196, 192 ,
	220, 184, 184 ,
	212, 176, 176 ,
	200, 160, 160 ,
	188, 148, 148 ,
	180, 140, 140 ,
	168, 128, 128 ,
	156, 116, 116 ,
	148, 104, 104 ,
	136, 96, 96 ,
	124, 84, 84 ,
	116, 76, 76 ,
	104, 64, 64 ,
	92, 56, 56 ,
	84, 48, 48 ,
	72, 40, 40 ,
	60, 32, 32 ,
	52, 24, 24 ,
	40, 20, 20 ,
	28, 12, 12 ,
	20, 8, 8 ,
	180, 80, 80 ,
	160, 56, 56 ,
	140, 40, 40 ,
	120, 24, 24 ,
	100, 12, 12 ,
	80, 4, 4 ,
	64, 0, 0 ,
	252, 240, 212 ,
	244, 224, 192 ,
	236, 208, 172 ,
	228, 192, 156 ,
	220, 176, 140 ,
	212, 160, 124 ,
	204, 148, 116 ,
	196, 140, 108 ,
	192, 132, 100 ,
	184, 128, 96 ,
	180, 120, 88 ,
	172, 116, 84 ,
	164, 108, 80 ,
	160, 104, 72 ,
	152, 96, 68 ,
	148, 92, 64 ,
	140, 88, 60 ,
	132, 80, 52 ,
	128, 76, 48 ,
	120, 72, 44 ,
	116, 64, 40 ,
	108, 60, 36 ,
	100, 56, 32 ,
	96, 52, 28 ,
	88, 48, 24 ,
	84, 44, 24 ,
	88, 40, 24 ,
	80, 32, 20 ,
	72, 28, 16 ,
	64, 24, 16 ,
	56, 20, 12 ,
	48, 16, 8 ,
	40, 12, 8 ,
	32, 12, 4 ,
	24, 8, 4 ,
	252, 252, 252 ,
	252, 244, 220 ,
	252, 236, 192 ,
	252, 228, 164 ,
	252, 224, 136 ,
	252, 224, 128 ,
	252, 228, 120 ,
	252, 208, 88 ,
	252, 184, 56 ,
	252, 160, 24 ,
	252, 128, 0 ,
	224, 108, 12 ,
	200, 96, 28 ,
	172, 84, 36 ,
	148, 72, 44 ,
	252, 252, 152 ,
	252, 236, 0 ,
	220, 164, 0 ,
	188, 108, 0 ,
	156, 60, 0 ,
	124, 28, 0 ,
	152, 0, 136
};

void CreatePlaypal(void)
{
	I_Printf("WOLF: Creating PLAYPAL lump...\n");

	epi::image_data_c *img = new epi::image_data_c(256, 32);

	const byte *src = wolf_palette;

	byte *dest = img->PixelAt(0, 0);

	for (; *src; src += 2)
	{
		for (int j = 0; j < src[0]; j++)
		{
			dest[0] = dest[1] = dest[2] = src[1]; //TODO: V767 https://www.viva64.com/en/w/v767/ Suspicious access to element of 'src' array by a constant index inside a loop.
			dest += 3;
		}
	}

	wlf_pal = R_UploadTexture(img, UPL_NONE);

	delete img;
}

void CreateROTTpal(void)
{
	I_Printf("ROTT: Creating PLAYPAL lump...\n");

	epi::image_data_c *img = new epi::image_data_c(256, 32);

	const byte *src = rott_palette;

	byte *dest = img->PixelAt(0, 0);

	for (; *src; src += 2)
	{
		for (int j = 0; j < src[0]; j++)
		{
			dest[0] = dest[1] = dest[2] = src[1]; //TODO: V767 https://www.viva64.com/en/w/v767/ Suspicious access to element of 'src' array by a constant index inside a loop.
			dest += 3;
		}
	}

	rott_pal = R_UploadTexture(img, UPL_NONE);

	delete img;
}