#  $FreeBSD: head/sys/boot/arm/at91/boot2/Makefile 251250 2013-06-02 11:44:23Z tijl $

.PATH: ${.CURDIR}/../libat91 ${.CURDIR}/../bootspi

P=boot2
FILES=${P}
SRCS=arm_init.S boot2.c ${BOOT_FLAVOR:tl}_board.c
MAN=
LDFLAGS=-e 0 -T ${.CURDIR}/../linker.cfg
OBJS+=  ${SRCS:N*.h:R:S/$/.o/g}

.include <bsd.prog.mk>

.if ${BOOT_FLAVOR} == "kb920x"
CFLAGS+=-DBOOT_IIC
.endif
CFLAGS+= \
	-I${.CURDIR}/../bootspi \
	-I${.CURDIR}/../../../common \
	-I${.CURDIR}/../../../.. \
	-D_KERNEL \
	-DUFS1_ONLY
