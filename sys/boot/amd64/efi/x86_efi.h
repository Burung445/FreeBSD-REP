/*-
 * Copyright (c) 2013 The FreeBSD Foundation
 * All rights reserved.
 *
 * This software was developed by Benno Rice under sponsorship from
 * the FreeBSD Foundation.
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
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD:  264095 2014-04-04 00:16:46Z emaste $
 */

#ifndef	_X86_EFI_COPY_H_
#define	_X86_EFI_COPY_H_

int	x86_efi_autoload(void);

int	x86_efi_getdev(void **vdev, const char *devspec, const char **path);
char	*x86_efi_fmtdev(void *vdev);
int	x86_efi_setcurrdev(struct env_var *ev, int flags, const void *value);

int	x86_efi_copy_init(void);
void	x86_efi_copy_finish(void);

ssize_t	x86_efi_copyin(const void *src, vm_offset_t dest, const size_t len);
ssize_t	x86_efi_copyout(const vm_offset_t src, void *dest, const size_t len);
ssize_t	x86_efi_readin(const int fd, vm_offset_t dest, const size_t len);

extern UINTN x86_efi_mapkey;

#endif	/* _X86_EFI_COPY_H_ */
