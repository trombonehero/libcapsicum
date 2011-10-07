PROG=	test-libcapsicum
INTERNALPROG=	yes
SRCS=	\
	ctest.c \
	main.c \
	fdlist.c \
	startfd.c \

NO_MAN=

CSTD?=	c99

# Use headers and libc from the build, if available.
KERNCONF?=	GENERIC
OBJROOT=	${.OBJDIR}/../../../../
OBJKERN=	${OBJROOT}/sys/${KERNCONF}

SRCROOT=	${.CURDIR}/../../../../

CFLAGS+=	-Wall -Werror -I${.CURDIR}/../src
LDFLAGS+=	-L../src -lcapsicum

all: ${PROG} run_tests
run_tests:
	sh ${.CURDIR}/test.t || exit 1

.include <bsd.prog.mk>
