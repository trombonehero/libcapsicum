PROG=	test-libcapsicum
INTERNALPROG=	yes
SRCS=	\
	ctest.c \
	main.c \
	fdlist.c \

NO_MAN=

CSTD?=	c99

# Use headers and libc from the build, if available.
KERNCONF?=	GENERIC
OBJROOT=	${.OBJDIR}/../../../../
OBJKERN=	${OBJROOT}/sys/${KERNCONF}

SRCROOT=	${.CURDIR}/../../../../

CFLAGS+=	-I${.CURDIR}/../src
LDFLAGS+=	-L../src -lcapsicum

.include <bsd.prog.mk>
