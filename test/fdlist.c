#include <sys/stat.h>

#include <string.h>
#include <unistd.h>

#include <libcapsicum.h>

#include "ctest.h"
#include "tests.h"

int
test_fdlist()
{
	int success = PASSED;
	cap_rights_t rights = CAP_READ | CAP_SEEK | CAP_FSTAT;
	const char *subsystem = "org.freebsd.libcapsicum.test";
	const char *classname = "File";
	struct lc_fdlist *fdlistp;
	int fd;
	struct stat tmpfile_stat;

	CHECK(lc_fdlist_global() == 0);

	fdlistp = lc_fdlist_new();
	CHECK(fdlistp != 0);

	// What we want is to be able to install an fdlist as the global one
	// without mucking about with shared memory segments ourselves.

	// Create a temporary file to put in the FD list.
	char tmpfilename[80];
	strncpy(tmpfilename, "/tmp/libcapsicum.test.XXXX", sizeof(tmpfilename));
	REQUIRE(fd = mkstemp(tmpfilename));
	CHECK_SYSCALL_SUCCEEDS(fstat, fd, &tmpfile_stat);

	// Put the temporary file's parent in the fdlist for relative lookup.
	const char dirname[] = "/tmp";
	int dirfd = open(dirname, O_RDONLY);

	struct stat dirstat;
	CHECK_SYSCALL_SUCCEEDS(fstat, dirfd, &dirstat);

	CHECK_SYSCALL_SUCCEEDS(lc_fdlist_addcap,
	    fdlistp, subsystem, classname, dirname, dirfd,
	    rights | CAP_LOOKUP);

	// Ensure that lc_fdlist_add() works.
	CHECK_SYSCALL_SUCCEEDS(lc_fdlist_add,
	    fdlistp, subsystem, classname, "raw", fd);

	const char *relative_name;
	int found;
	REQUIRE(found = lc_fdlist_find(
	    fdlistp, subsystem, classname, "raw", &relative_name));

	CHECK(found == fd);
	CHECK(strnlen(relative_name, 1) == 0);

	// Check lc_fdlist_addcap().
	CHECK_SYSCALL_SUCCEEDS(lc_fdlist_addcap,
	    fdlistp, subsystem, classname, "raw_cap", fd, rights);

	REQUIRE(found = lc_fdlist_find(
	    fdlistp, subsystem, classname, "raw_cap", &relative_name));

	CHECK(found != fd);

	cap_rights_t rights_out;
	CHECK_SYSCALL_SUCCEEDS(cap_getrights, found, &rights_out);
	CHECK(rights_out == rights);

	// Check relative lookup: we should find the parent dir, relative to
	// which we can open the actual file.
	REQUIRE(found = lc_fdlist_find(
	    fdlistp, subsystem, classname, tmpfilename, &relative_name));

	CHECK(strncmp(relative_name, tmpfilename + sizeof(dirname), 80)
		== 0);

	struct stat found_stat;
	CHECK_SYSCALL_SUCCEEDS(fstat, found, &found_stat);
	CHECK(found_stat.st_ino == dirstat.st_ino);

	REQUIRE(found = openat(found, relative_name, O_RDONLY));
	CHECK_SYSCALL_SUCCEEDS(fstat, found, &found_stat);

	return success;
}

