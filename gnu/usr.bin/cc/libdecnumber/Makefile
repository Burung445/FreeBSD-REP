# $FreeBSD: head/gnu/usr.bin/cc/libdecnumber/Makefile 245539 2013-01-17 05:56:28Z andrew $

.include <bsd.own.mk>

# Use our headers in preference to ones from ../cc_tools.
CFLAGS+=	-I${.CURDIR} -I.

.include "../Makefile.inc"

.PATH: ${GCCLIB}/libdecnumber

LIB=	decnumber
SRCS=	decNumber.c decContext.c decUtility.c \
        decimal32.c decimal64.c decimal128.c

INTERNALLIB=
WARNS?=	1

.include <bsd.lib.mk>
