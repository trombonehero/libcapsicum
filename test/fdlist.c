#include <string.h>
#include <unistd.h>

#include <libcapsicum.h>

#include "ctest.h"
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

	fdlistp = lc_fdlist_new();
	CHECK(fdlistp != 0);

	// What we want is to be able to install an fdlist as the global one
	// without mucking about with shared memory segments ourselves.

	// Create a temporary file to put in the FD list.
	char tmpfilename[80];
	strncpy(tmpfilename, "/tmp/libcapsicum.test.XXXX", sizeof(tmpfilename));
	REQUIRE(fd = mkstemp(tmpfilename));

	CHECK_SYSCALL_SUCCEEDS(lc_fdlist_add,
	    fdlistp, subsystem, classname, "raw", fd);

	return success;
}

