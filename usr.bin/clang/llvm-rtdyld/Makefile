# $FreeBSD: head/usr.bin/clang/llvm-rtdyld/Makefile 262613 2014-02-28 18:06:00Z dim $

MAN=
.include <bsd.own.mk>

PROG_CXX=llvm-rtdyld
DPADD=	${LIBZ}
LDADD=	-lz

SRCDIR=	tools/llvm-rtdyld
SRCS=	llvm-rtdyld.cpp

LIBDEPS=llvmdebuginfo \
	llvmjit \
	llvmexecutionengine \
	llvmruntimedyld \
	llvmarmdisassembler \
	llvmarmcodegen \
	llvmarmasmparser \
	llvmarmdesc \
	llvmarminfo \
	llvmarminstprinter \
	llvmmipsdisassembler \
	llvmmipscodegen \
	llvmmipsasmparser \
	llvmmipsdesc \
	llvmmipsinfo \
	llvmmipsinstprinter \
	llvmpowerpccodegen \
	llvmpowerpcasmparser \
	llvmpowerpcdesc \
	llvmpowerpcinfo \
	llvmpowerpcinstprinter \
	llvmsparcdisassembler \
	llvmsparccodegen \
	llvmsparcasmparser \
	llvmsparcdesc \
	llvmsparcinfo \
	llvmsparcinstprinter \
	llvmx86disassembler \
	llvmx86asmparser \
	llvmx86codegen \
	llvmselectiondag \
	llvmasmprinter \
	llvmmcparser \
	llvmcodegen \
	llvmobjcarcopts \
	llvmscalaropts \
	llvminstcombine \
	llvmtransformutils \
	llvmipa \
	llvmanalysis \
	llvmx86desc \
	llvmx86info \
	llvmtarget \
	llvmx86instprinter \
	llvmmc \
	llvmobject \
	llvmx86utils \
	llvmcore \
	llvmsupport

.include "../clang.prog.mk"
