# $FreeBSD: head/sys/modules/wlan_wep/Makefile 182668 2008-09-01 23:59:00Z imp $

.PATH: ${.CURDIR}/../../net80211

KMOD=	wlan_wep
SRCS=	ieee80211_crypto_wep.c
SRCS+=	opt_wlan.h

.if !defined(KERNBUILDDIR)
opt_wlan.h:
	echo "#define IEEE80211_DEBUG 1" > ${.TARGET}
.endif

.include <bsd.kmod.mk>
