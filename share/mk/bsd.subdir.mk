#	from: @(#)bsd.subdir.mk	5.9 (Berkeley) 2/1/91
# $FreeBSD: head/share/mk/bsd.subdir.mk 251749 2013-06-14 16:25:41Z sjg $
#
# The include file <bsd.subdir.mk> contains the default targets
# for building subdirectories.
#
# For all of the directories listed in the variable SUBDIRS, the
# specified directory will be visited and the target made. There is
# also a default target which allows the command "make subdir" where
# subdir is any directory listed in the variable SUBDIRS.
#
#
# +++ variables +++
#
# DISTRIBUTION	Name of distribution. [base]
#
# SUBDIR	A list of subdirectories that should be built as well.
#		Each of the targets will execute the same target in the
#		subdirectories.
#
# +++ targets +++
#
#	distribute:
# 		This is a variant of install, which will
# 		put the stuff into the right "distribution".
#
#	afterinstall, all, all-man, beforeinstall, checkdpadd, clean,
#	cleandepend, cleandir, cleanilinks depend, install, lint,
#	maninstall, manlint, obj, objlink, realinstall, regress, tags
#

.if !target(__<bsd.subdir.mk>__)
__<bsd.subdir.mk>__:

.include <bsd.init.mk>

DISTRIBUTION?=	base
.if !target(distribute)
distribute: .MAKE
.for dist in ${DISTRIBUTION}
	${_+_}cd ${.CURDIR}; \
	    ${MAKE} install -DNO_SUBDIR DESTDIR=${DISTDIR}/${dist} SHARED=copies
.endfor
.endif

_SUBDIR: .USE .MAKE
.if defined(SUBDIR) && !empty(SUBDIR) && !defined(NO_SUBDIR)
	@${_+_}set -e; for entry in ${SUBDIR:N.WAIT}; do \
		if test -d ${.CURDIR}/$${entry}.${MACHINE_ARCH}; then \
			${ECHODIR} "===> ${DIRPRFX}$${entry}.${MACHINE_ARCH} (${.TARGET:realinstall=install})"; \
			edir=$${entry}.${MACHINE_ARCH}; \
			cd ${.CURDIR}/$${edir}; \
		else \
			${ECHODIR} "===> ${DIRPRFX}$$entry (${.TARGET:realinstall=install})"; \
			edir=$${entry}; \
			cd ${.CURDIR}/$${edir}; \
		fi; \
		${MAKE} ${.TARGET:realinstall=install} \
		    DIRPRFX=${DIRPRFX}$$edir/; \
	done
.endif

${SUBDIR:N.WAIT}: .PHONY .MAKE
	${_+_}@if test -d ${.TARGET}.${MACHINE_ARCH}; then \
		cd ${.CURDIR}/${.TARGET}.${MACHINE_ARCH}; \
	else \
		cd ${.CURDIR}/${.TARGET}; \
	fi; \
	${MAKE} all

# Work around parsing of .if nested in .for by putting .WAIT string into a var.
__wait= .WAIT
.for __target in all all-man checkdpadd clean cleandepend cleandir \
    cleanilinks depend distribute lint maninstall manlint obj objlink \
    realinstall regress tags ${SUBDIR_TARGETS}
.ifdef SUBDIR_PARALLEL
__subdir_targets=
.for __dir in ${SUBDIR}
.if ${__wait} == ${__dir}
__subdir_targets+= .WAIT
.else
__subdir_targets+= ${__target}_subdir_${__dir}
${__target}_subdir_${__dir}: .MAKE
	@${_+_}set -e; \
		if test -d ${.CURDIR}/${__dir}.${MACHINE_ARCH}; then \
			${ECHODIR} "===> ${DIRPRFX}${__dir}.${MACHINE_ARCH} (${__target:realinstall=install})"; \
			edir=${__dir}.${MACHINE_ARCH}; \
			cd ${.CURDIR}/$${edir}; \
		else \
			${ECHODIR} "===> ${DIRPRFX}${__dir} (${__target:realinstall=install})"; \
			edir=${__dir}; \
			cd ${.CURDIR}/$${edir}; \
		fi; \
		${MAKE} ${__target:realinstall=install} \
		    DIRPRFX=${DIRPRFX}$$edir/
.endif
.endfor
${__target}: ${__subdir_targets}
.else
${__target}: _SUBDIR
.endif
.endfor

.for __target in files includes
.for __stage in build install
${__stage}${__target}:
.if make(${__stage}${__target})
${__stage}${__target}: _SUBDIR
.endif
.endfor
${__target}: .MAKE
	${_+_}set -e; cd ${.CURDIR}; ${MAKE} build${__target}; ${MAKE} install${__target}
.endfor

.if !target(install)
.if !target(beforeinstall)
beforeinstall:
.endif
.if !target(afterinstall)
afterinstall:
.endif
install: beforeinstall realinstall afterinstall
.ORDER: beforeinstall realinstall afterinstall
.endif

.endif
