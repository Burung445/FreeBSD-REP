/*-
 * Copyright 2005 Colin Percival
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: head/sys/crypto/sha2/sha256.h 263218 2014-03-16 01:43:23Z jmg $
 */

#ifndef _SHA256_H_
#define _SHA256_H_

#ifndef _KERNEL
#include <sys/types.h>
#endif

typedef struct SHA256Context {
	uint32_t state[8];
	uint64_t count;
	uint8_t buf[64];
} SHA256_CTX;

__BEGIN_DECLS
void	SHA256_Init(SHA256_CTX *);
void	SHA256_Update(SHA256_CTX *, const void *, size_t);
void	SHA256_Final(unsigned char [32], SHA256_CTX *);
char   *SHA256_End(SHA256_CTX *, char *);
char   *SHA256_Data(const void *, unsigned int, char *);
#ifndef _KERNEL
char   *SHA256_File(const char *, char *);
char   *SHA256_FileChunk(const char *, char *, off_t, off_t);
#endif
__END_DECLS

#endif /* !_SHA256_H_ */
