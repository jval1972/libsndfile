/*
** Copyright (C) 2005-2014 Erik de Castro Lopo <erikd@mega-nerd.com>
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

/*
**	Autoconf leaves many config parameters undefined.
**	Here we change then from being undefined to defining them to 0.
**	This allows things like:
**
**		#if HAVE_CONFIG_PARAM
**
**	and
**
**		if (HAVE_CONFIG_PARAM)
**			do_something () ;
*/

#ifndef SFCONFIG_H
#define SFCONFIG_H

#define ssize_t int

#define PACKAGE "libsndfile"
#define PACKAGE_NAME "libsndfile"
#define VERSION "1.0.28"
#define PACKAGE_VERSION "1.0.28"
#define PRId64   "%I64d"
#define CPU_IS_LITTLE_ENDIAN 1
#define CPU_IS_BIG_ENDIAN 0
#define SIZEOF_SF_COUNT_T 8

/* Include the Autoconf generated file. */
#include "config.h"

/* Now fiddle the values. */

#ifndef HAVE_ALSA_ASOUNDLIB_H
#define HAVE_ALSA_ASOUNDLIB_H 0
#endif

#ifndef HAVE_BYTESWAP_H
#define HAVE_BYTESWAP_H 0
#endif

#ifndef HAVE_DECL_S_IRGRP
#define	HAVE_DECL_S_IRGRP 0
#endif

#ifndef HAVE_ENDIAN_H
#define HAVE_ENDIAN_H 0
#endif

#ifndef HAVE_FSTAT64
#define HAVE_FSTAT64 0
#endif

#ifndef HAVE_FSYNC
#define HAVE_FSYNC 0
#endif

#ifndef HAVE_LOCALE_H
#define HAVE_LOCALE_H 0
#endif

#ifndef HAVE_LRINT
#define HAVE_LRINT 0
#endif

#ifndef HAVE_LRINTF
#define HAVE_LRINTF 0
#endif

#ifndef HAVE_MMAP
#define HAVE_MMAP 0
#endif

#ifndef HAVE_SETLOCALE
#define HAVE_SETLOCALE 0
#endif

#ifndef HAVE_SQLITE3
#define HAVE_SQLITE3 0
#endif

#ifndef HAVE_STDINT_H
#define HAVE_STDINT_H 0
#endif

#ifndef HAVE_SYS_WAIT_H
#define HAVE_SYS_WAIT_H 0
#endif

#ifndef HAVE_SYS_TIME_H
#define HAVE_SYS_TIME_H 0
#endif

#ifndef HAVE_UNISTD_H
#define HAVE_UNISTD_H 0
#endif

#ifndef HAVE_PIPE
#define HAVE_PIPE 0
#endif

#ifndef HAVE_WAITPID
#define	HAVE_WAITPID 0
#endif

#ifndef HAVE_X86INTRIN_H
#define HAVE_X86INTRIN_H 0
#endif

#define CPU_IS_X86		(defined __i486__ || defined __i586__ || defined __i686__ || defined __x86_64__)
#define CPU_IS_X86_64	(defined __x86_64__)

#endif
