/*-
 * Copyright (c) 2010 by Peter Jeremy <peterjeremy@acm.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: head/tools/test/testfloat/sparc64/fpu_reg.h 207151 2010-04-24 12:11:41Z marius $
 */

#ifndef _TESTFLOAT_SPARC64_FPU_REG_H_
#define	_TESTFLOAT_SPARC64_FPU_REG_H_

#include <sys/types.h>
extern u_int32_t __fpreg[64];

static __inline u_int32_t
__fpu_getreg(int r)
{

	return (__fpreg[r]);
}

static __inline u_int64_t
__fpu_getreg64(int r)
{

	return ((u_int64_t)__fpreg[r] << 32 | (u_int64_t)__fpreg[r + 1]);
}

static __inline void
__fpu_setreg(int r, u_int32_t v)
{

	__fpreg[r] = v;
}

static __inline void
__fpu_setreg64(int r, u_int64_t v)
{

	__fpreg[r] = (u_int32_t)(v >> 32);
	__fpreg[r + 1] = (u_int32_t)v;
}

#endif /* _TESTFLOAT_SPARC64_FPU_REG_H_ */
