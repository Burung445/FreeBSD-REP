# $FreeBSD: head/lib/atf/libatf-c/tests/detail/Makefile 263161 2014-03-14 08:56:19Z jmmv $

.include <bsd.init.mk>

TESTSDIR=	${TESTSBASE}/lib/atf/libatf-c/detail

ATF=		${.CURDIR:H:H:H:H:H}/contrib/atf
.PATH:		${ATF}/atf-c/detail

CFLAGS+=	-I${ATF}

.for _T in	dynstr_test \
		env_test \
		fs_test \
		list_test \
		map_test \
		process_test \
		sanity_test \
		text_test \
		user_test
ATF_TESTS_C+=	${_T}
SRCS.${_T}=	${_T}.c test_helpers.c
.endfor

.for p in process_helpers version_helper
PROGS+=		${p}
SRCS.${p}=	${p}.c
MAN.${p}=	# defined
BINDIR.${p}=	${TESTSDIR}
.endfor
version_helper.o: atf-version

.include "../../../common.mk"
.include <bsd.test.mk>
