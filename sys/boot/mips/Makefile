# $FreeBSD: head/sys/boot/mips/Makefile 262406 2014-02-23 22:20:52Z rwatson $

#
# The BERI boot loader port works only on 64-bit MIPS; not a hard port to
# 32-bit if someone is interested.  Build on all 64-bit MIPS platforms to
# ensure it gets adequate build-test coverage.
#
.if ${MACHINE_ARCH} == "mips64"
SUBDIR=	beri
.endif

.include <bsd.subdir.mk>
