# $FreeBSD: head/sys/modules/wi/Makefile 253826 2013-07-31 01:42:59Z jhibbits $

.PATH: ${.CURDIR}/../../dev/wi

KMOD=	if_wi
SRCS=	if_wi.c if_wi_pccard.c if_wi_pci.c \
	card_if.h device_if.h bus_if.h pci_if.h pccarddevs.h \
	opt_wlan.h

.if ${MACHINE_CPUARCH} == "powerpc"
SRCS+=	if_wi_macio.c
SRCS+=	ofw_bus_if.h
.endif

.include <bsd.kmod.mk>
