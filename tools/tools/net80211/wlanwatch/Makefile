# $FreeBSD: head/tools/tools/net80211/wlanwatch/Makefile 160779 2006-07-28 10:59:27Z yar $

PROG=	wlanwatch
BINDIR=	/usr/local/bin
MAN=

.include <src.opts.mk>

.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+= -DINET6
.endif

.include <bsd.prog.mk>
