/* $FreeBSD: head/lib/libblocksruntime/config.h 215125 2010-11-11 15:13:11Z ed $ */

/* #undef HAVE_SYS_BYTEORDER_H */
/* #undef HAVE_AVAILABILITY_MACROS_H */
/* #undef HAVE_TARGET_CONDITIONALS_H */
/* #undef HAVE_LIBKERN_OSATOMIC_H */

#define HAVE_SYSCONF 1

/* #undef HAVE_OSATOMIC_COMPARE_AND_SWAP_INT */
/* #undef HAVE_OSATOMIC_COMPARE_AND_SWAP_LONG */

#define HAVE_SYNC_BOOL_COMPARE_AND_SWAP_INT 1
#define HAVE_SYNC_BOOL_COMPARE_AND_SWAP_LONG 1
