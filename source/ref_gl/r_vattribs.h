/*
Copyright (C) 2013 Victor Luchits

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#ifndef __R_VATTRIBS_H__
#define __R_VATTRIBS_H__

typedef enum vattrib_e
{
	VATTRIB_POSITION		= 0,

	VATTRIB_NORMAL			= 1,

	VATTRIB_SVECTOR			= 2,

	VATTRIB_COLOR			= 3,

	VATTRIB_TEXCOORDS		= 4,

	VATTRIB_SPRITEPOINT		= 5,
	VATTRIB_SPRITERAXIS		= 6,
	VATTRIB_SPRITEUAXIS		= 7,

	VATTRIB_BONESINDICES	= 8,
	VATTRIB_BONESWEIGHTS	= 9,

	VATTRIB_COLOR1			= 8,
	VATTRIB_COLOR2			= 9,
	VATTRIB_COLOR3			= 10,

	VATTRIB_LMCOORDS		= 8,
	VATTRIB_LMCOORDS1		= 9,
	VATTRIB_LMCOORDS2		= 10,
	VATTRIB_LMCOORDS3		= 11,

	VATTRIB_INSTANCE_QUAT	= 12,
	VATTRIB_INSTANCE_XYZS	= 13,

	NUM_VERTEX_ATTRIBS		= 14
} vattrib_t;

#define VATTRIB_BIT(va)		(1<<(va))

typedef enum vattribbit_e
{
	VATTRIB_POSITION_BIT	= VATTRIB_BIT(0),

	VATTRIB_NORMAL_BIT		= VATTRIB_BIT(1),

	VATTRIB_SVECTOR_BIT		= VATTRIB_BIT(2),

	VATTRIB_COLOR_BIT		= VATTRIB_BIT(3),

	VATTRIB_TEXCOORDS_BIT	= VATTRIB_BIT(4),

	VATTRIB_AUTOSPRITE_BIT	= VATTRIB_BIT(5),
	VATTRIB_AUTOSPRITE2_BIT	= VATTRIB_BIT(6),

	VATTRIB_BONESINDICES_BIT= VATTRIB_BIT(7),
	VATTRIB_BONESWEIGHTS_BIT= VATTRIB_BIT(8),

	VATTRIB_BONES_BIT		= VATTRIB_BONESINDICES_BIT|VATTRIB_BONESWEIGHTS_BIT,

	VATTRIB_COLOR1_BIT		= VATTRIB_BIT(9),
	VATTRIB_COLOR2_BIT		= VATTRIB_BIT(10),
	VATTRIB_COLOR3_BIT		= VATTRIB_BIT(11),

	VATTRIB_LMCOORDS_BIT	= VATTRIB_BIT(12),
	VATTRIB_LMCOORDS1_BIT	= VATTRIB_BIT(13),
	VATTRIB_LMCOORDS2_BIT	= VATTRIB_BIT(14),
	VATTRIB_LMCOORDS3_BIT	= VATTRIB_BIT(15),

	VATTRIB_INSTANCE_QUAT_BIT= VATTRIB_BIT(16),
	VATTRIB_INSTANCE_XYZS_BIT= VATTRIB_BIT(17),

	VATTRIB_INSTANCES_BIT	= VATTRIB_INSTANCE_QUAT_BIT|VATTRIB_INSTANCE_XYZS_BIT,

	VATTRIBS_MASK			= VATTRIB_BIT(18)-1
} vattribbit_t;

typedef unsigned int vattribmask_t;

#endif
