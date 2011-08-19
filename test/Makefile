PROG=	test-libcapsicum
SRCS=	\
	ctest.c \
	main.c \
	fdlist.c \

NO_MAN=

# Use headers and libc from the build, if available.
KERNCONF?=	GENERIC
OBJROOT=	${.OBJDIR}/../../../../
OBJKERN=	${OBJROOT}/sys/${KERNCONF}

SRCROOT=	${.CURDIR}/../../../../

CFLAGS+=	-I${OBJKERN} -I${SRCROOT}/sys
LDFLAGS+=	-L${OBJROOT}/lib/libc -lc

.include <bsd.prog.mk>
