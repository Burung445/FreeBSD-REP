#	@(#)Makefile	8.1 (Berkeley) 6/5/93
# $FreeBSD: head/sbin/ping/Makefile 263240 2014-03-16 13:43:06Z jilles $

.include <src.opts.mk>

PROG=	ping
MAN=	ping.8
BINOWN=	root
BINMODE=4555
WARNS?=	2
DPADD=	${LIBM}
LDADD=	-lm

.if ${MK_CASPER} != "no" && !defined(RESCUE)
DPADD+=	${LIBCAPSICUM} ${LIBNV}
LDADD+=	-lcapsicum -lnv
CFLAGS+=-DHAVE_LIBCAPSICUM
.endif

.if !defined(RELEASE_CRUNCH)
CFLAGS+=-DIPSEC
DPADD+=	${LIBIPSEC}
LDADD+=	-lipsec
.endif

.include <bsd.prog.mk>
