#	@(#)Makefile	8.2 (Berkeley) 1/25/94
# $FreeBSD: head/usr.bin/mail/Makefile 201386 2010-01-02 10:27:05Z ed $

PROG=	mail
SRCS=	version.c cmd1.c cmd2.c cmd3.c cmdtab.c collect.c edit.c fio.c \
	getname.c head.c v7.local.c lex.c list.c main.c names.c popen.c \
	quit.c send.c strings.c temp.c tty.c util.c vars.c
FILES=	mail.help mail.tildehelp
FILESDIR=	${SHAREDIR}/misc
EFILES=	mail.rc
LINKS=	${BINDIR}/mail ${BINDIR}/Mail ${BINDIR}/mail ${BINDIR}/mailx
MLINKS=	mail.1 Mail.1 mail.1 mailx.1

WARNS?=	1

.PATH: ${.CURDIR}/misc

etc-mailrc:
	cd ${.CURDIR}/misc; ${INSTALL} -o root -g wheel \
	    -m 644 ${EFILES} ${DESTDIR}/etc

.include <bsd.prog.mk>
