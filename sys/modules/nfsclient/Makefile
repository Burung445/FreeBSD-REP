# $FreeBSD: head/sys/modules/nfsclient/Makefile 258541 2013-11-25 07:38:45Z attilio $

.PATH: ${.CURDIR}/../../nfsclient ${.CURDIR}/../../nfs ${.CURDIR}/../../rpc

KMOD=	nfsclient
SRCS=	vnode_if.h \
	nfs_bio.c nfs_node.c nfs_subs.c nfs_nfsiod.c \
	nfs_vfsops.c nfs_vnops.c nfs_krpc.c \
	opt_inet.h opt_nfs.h opt_bootp.h opt_nfsroot.h
SRCS+=	opt_inet6.h opt_kgssapi.h

.if !defined(KERNBUILDDIR)
NFS_INET?=	1	# 0/1 - requires INET to be configured in kernel
NFS_INET6?=	1	# 0/1 - requires INET6 to be configured in kernel
NFS_ROOT?=	1	# 0/1 - requires NFS_ROOT to be configured in kernel

.if ${NFS_INET} > 0
opt_inet.h:
	echo "#define INET 1" > ${.TARGET}
.endif

.if ${NFS_INET6} > 0
opt_inet6.h:
	echo "#define INET6 1" > ${.TARGET}
.endif

.if ${NFS_ROOT} > 0
opt_nfsroot.h:
	echo "#define NFS_ROOT 1" > ${.TARGET}
.endif
.else
OPT_NFS_ROOT!=	cat ${KERNBUILDDIR}/opt_nfsroot.h
.if empty(OPT_NFS_ROOT)
NFS_ROOT=	0
.else
NFS_ROOT=	1
.endif
.endif

.if ${NFS_ROOT} > 0
SRCS+=	nfs_diskless.c
.endif

.include <bsd.kmod.mk>
