#	@(#)Makefile	8.1 (Berkeley) 5/31/93
# $FreeBSD: head/games/fortune/fortune/Makefile 203923 2010-02-15 14:32:00Z uqs $

PROG=	fortune
MAN=	fortune.6
CFLAGS+=-DDEBUG -I${.CURDIR}/../strfile

.include <bsd.prog.mk>

test:	${PROG}
	./${PROG} -m brass
