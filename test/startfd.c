#include <sys/types.h>

#include <sys/stat.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libcapsicum.h>

#include "ctest.h"
#include "tests.h"


int
test_startfd()
{
	int success = PASSED;
	const char *bin_name = getenv("BINARY");
	struct lc_fdlist *fdlistp = lc_fdlist_new();

	CHECK(bin_name != NULL);
	CHECK(strnlen(bin_name, 1) > 0);

	char* const argv[] = { (char*) bin_name, NULL };

	struct lc_sandbox *sandbox;
	CHECK_SYSCALL_SUCCEEDS(lch_start,
		bin_name, argv, LCH_PERMIT_STDOUT | LCH_PERMIT_STDERR,
		fdlistp, &sandbox);

	pid_t pid;
	CHECK_SYSCALL_SUCCEEDS(lch_getpid, sandbox, &pid);

	int status;
	CHECK_SYSCALL_SUCCEEDS(wait, &status);
	CHECK(WIFEXITED(status));
	CHECK(WEXITSTATUS(status) == SANDBOX_MAGIC);

	return success;
}

