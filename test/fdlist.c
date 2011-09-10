#include <libcapsicum.h>

#include "tests.h"

int
test_fdlist()
{
	int success = PASSED;
	const char *subsystem = "org.freebsd.libcapsicum.test";
	const char *classname = "File";
	struct lc_fdlist *fdlistp;
	int fd;

	CHECK(lc_fdlist_global() == 0);

	fdlistp = lc_fdlist_global();
	CHECK(fdlistp != 0);

	// What we want is to be able to install an fdlist as the global one
	// without mucking about with shared memory segments ourselves.

	CHECK(lc_fdlist_size(fdlistp) == 0);

	REQUIRE(fd = open("/tmp/libcapsicum.fdlist", O_RDWR | O_CREAT));

	CHECK(lc_fdlist_add(fdlistp,
	    subsystem, classname, "raw", fd) == 0);

	return success;
}

