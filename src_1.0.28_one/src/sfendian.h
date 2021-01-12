/*
** Copyright (C) 1999-2016 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 2.1 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef SFENDIAN_INCLUDED
#define SFENDIAN_INCLUDED

#include "sfconfig.h"

#include <stdint.h>

#define	ENDSWAP_16(x)		((((x) >> 8) & 0xFF) + (((x) & 0xFF) << 8))
#define	ENDSWAP_32(x)		((((x) >> 24) & 0xFF) + (((x) >> 8) & 0xFF00) + (((x) & 0xFF00) << 8) + (((x) & 0xFF) << 24))

static uint64_t
ENDSWAP_64 (uint64_t x)
{	union
	{	uint32_t parts [2] ;
		uint64_t whole ;
	} u ;
	uint32_t temp ;

	u.whole = x ;
	temp = u.parts [0] ;
	u.parts [0] = ENDSWAP_32 (u.parts [1]) ;
	u.parts [1] = ENDSWAP_32 (temp) ;
	return u.whole ;
}

/*
** Many file types (ie WAV, AIFF) use sets of four consecutive bytes as a
** marker indicating different sections of the file.
** The following MAKE_MARKER macro allows th creation of integer constants
** for these markers.
*/

#define CPU_IS_LITTLE_ENDIAN 1
#define CPU_IS_BIG_ENDIAN 0

/*
** Macros to handle reading of data of a specific endian-ness into host endian
** shorts and ints. The single input is an unsigned char* pointer to the start
** of the object. There are two versions of each macro as we need to deal with
** both big and little endian CPUs.
*/

#if (CPU_IS_LITTLE_ENDIAN == 1)
	#define LE2H_16(x)			(x)
	#define LE2H_32(x)			(x)

	#define BE2H_16(x)			ENDSWAP_16 (x)
	#define BE2H_32(x)			ENDSWAP_32 (x)
	#define BE2H_64(x)			ENDSWAP_64 (x)

	#define H2BE_16(x)			ENDSWAP_16 (x)
	#define H2BE_32(x)			ENDSWAP_32 (x)

	#define H2LE_16(x)			(x)
	#define H2LE_32(x)			(x)

#elif (CPU_IS_BIG_ENDIAN == 1)
	#define LE2H_16(x)			ENDSWAP_16 (x)
	#define LE2H_32(x)			ENDSWAP_32 (x)

	#define BE2H_16(x)			(x)
	#define BE2H_32(x)			(x)
	#define	BE2H_64(x)			(x)

	#define H2BE_16(x)			(x)
	#define H2BE_32(x)			(x)

	#define H2LE_16(x)			ENDSWAP_16 (x)
	#define H2LE_32(x)			ENDSWAP_32 (x)

#else
	#error "Target CPU endian-ness unknown. May need to hand edit src/sfconfig.h"
#endif

#define LET2H_16_PTR(x)			((x) [1] + ((x) [2] << 8))
#define LET2H_32_PTR(x)			(((x) [0] << 8) + ((x) [1] << 16) + ((x) [2] << 24))

#define BET2H_16_PTR(x)			(((x) [0] << 8) + (x) [1])
#define BET2H_32_PTR(x)			(((x) [0] << 24) + ((x) [1] << 16) + ((x) [2] << 8))

static void
psf_put_be64 (uint8_t *ptr, int offset, int64_t value)
{
	ptr [offset] = value >> 56 ;
	ptr [offset + 1] = value >> 48 ;
	ptr [offset + 2] = value >> 40 ;
	ptr [offset + 3] = value >> 32 ;
	ptr [offset + 4] = value >> 24 ;
	ptr [offset + 5] = value >> 16 ;
	ptr [offset + 6] = value >> 8 ;
	ptr [offset + 7] = value ;
} /* psf_put_be64 */

static void
psf_put_be32 (uint8_t *ptr, int offset, int32_t value)
{
	ptr [offset] = value >> 24 ;
	ptr [offset + 1] = value >> 16 ;
	ptr [offset + 2] = value >> 8 ;
	ptr [offset + 3] = value ;
} /* psf_put_be32 */

static void
psf_put_be16 (uint8_t *ptr, int offset, int16_t value)
{
	ptr [offset] = value >> 8 ;
	ptr [offset + 1] = value ;
} /* psf_put_be16 */

static int64_t
psf_get_be64 (uint8_t *ptr, int offset)
{	int64_t value ;

	value = ((uint32_t) ptr [offset]) << 24 ;
	value += ptr [offset + 1] << 16 ;
	value += ptr [offset + 2] << 8 ;
	value += ptr [offset + 3] ;

	value = ((uint64_t) value) << 32 ;

	value += ((uint32_t) ptr [offset + 4]) << 24 ;
	value += ptr [offset + 5] << 16 ;
	value += ptr [offset + 6] << 8 ;
	value += ptr [offset + 7] ;
	return value ;
} /* psf_get_be64 */

static int64_t
psf_get_le64 (uint8_t *ptr, int offset)
{	int64_t value ;

	value = ((uint32_t) ptr [offset + 7]) << 24 ;
	value += ptr [offset + 6] << 16 ;
	value += ptr [offset + 5] << 8 ;
	value += ptr [offset + 4] ;

	value = ((uint64_t) value) << 32 ;

	value += ((uint32_t) ptr [offset + 3]) << 24 ;
	value += ptr [offset + 2] << 16 ;
	value += ptr [offset + 1] << 8 ;
	value += ptr [offset] ;
	return value ;
} /* psf_get_le64 */

static int32_t
psf_get_be32 (uint8_t *ptr, int offset)
{	int32_t value ;

	value = ((uint32_t) ptr [offset]) << 24 ;
	value += ptr [offset + 1] << 16 ;
	value += ptr [offset + 2] << 8 ;
	value += ptr [offset + 3] ;
	return value ;
} /* psf_get_be32 */

static int32_t
psf_get_le32 (uint8_t *ptr, int offset)
{	int32_t value ;

	value = ((uint32_t) ptr [offset + 3]) << 24 ;
	value += ptr [offset + 2] << 16 ;
	value += ptr [offset + 1] << 8 ;
	value += ptr [offset] ;
	return value ;
} /* psf_get_le32 */

static int32_t
psf_get_be24 (uint8_t *ptr, int offset)
{	int32_t value ;

	value = ((uint32_t) ptr [offset]) << 24 ;
	value += ptr [offset + 1] << 16 ;
	value += ptr [offset + 2] << 8 ;
	return value ;
} /* psf_get_be24 */

static int32_t
psf_get_le24 (uint8_t *ptr, int offset)
{	int32_t value ;

	value = ((uint32_t) ptr [offset + 2]) << 24 ;
	value += ptr [offset + 1] << 16 ;
	value += ptr [offset] << 8 ;
	return value ;
} /* psf_get_le24 */

static int16_t
psf_get_be16 (uint8_t *ptr, int offset)
{	return (ptr [offset] << 8) + ptr [offset + 1] ;
} /* psf_get_be16 */

/*-----------------------------------------------------------------------------------------------
** Generic functions for performing endian swapping on integer arrays.
*/

static void
endswap_short_array (short *ptr, int len)
{	short	temp ;

	while (--len >= 0)
	{	temp = ptr [len] ;
		ptr [len] = ENDSWAP_16 (temp) ;
		} ;
} /* endswap_short_array */

static void
endswap_short_copy (short *dest, const short *src, int len)
{
	while (--len >= 0)
	{	dest [len] = ENDSWAP_16 (src [len]) ;
		} ;
} /* endswap_short_copy */

static void
endswap_int_array (int *ptr, int len)
{	int temp ;

	while (--len >= 0)
	{	temp = ptr [len] ;
		ptr [len] = ENDSWAP_32 (temp) ;
		} ;
} /* endswap_int_array */

static void
endswap_int_copy (int *dest, const int *src, int len)
{
	while (--len >= 0)
	{	dest [len] = ENDSWAP_32 (src [len]) ;
		} ;
} /* endswap_int_copy */

/*========================================================================================
*/

static void
endswap_int64_t_array (int64_t *ptr, int len)
{	int64_t value ;

	while (--len >= 0)
	{	value = ptr [len] ;
		ptr [len] = ENDSWAP_64 (value) ;
		} ;
} /* endswap_int64_t_array */

static void
endswap_int64_t_copy (int64_t *dest, const int64_t *src, int len)
{	int64_t value ;

	while (--len >= 0)
	{	value = src [len] ;
		dest [len] = ENDSWAP_64 (value) ;
		} ;
} /* endswap_int64_t_copy */

/* A couple of wrapper functions. */

static void
endswap_float_array (float *ptr, int len)
{	endswap_int_array ((int *) ptr, len) ;
} /* endswap_float_array */

static void
endswap_double_array (double *ptr, int len)
{	endswap_int64_t_array ((int64_t *) ptr, len) ;
} /* endswap_double_array */

static void
endswap_float_copy (float *dest, const float *src, int len)
{	endswap_int_copy ((int *) dest, (const int *) src, len) ;
} /* endswap_float_copy */

static void
endswap_double_copy (double *dest, const double *src, int len)
{	endswap_int64_t_copy ((int64_t *) dest, (const int64_t *) src, len) ;
} /* endswap_double_copy */

#endif /* SFENDIAN_INCLUDED */

