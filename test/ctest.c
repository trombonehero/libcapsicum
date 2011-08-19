#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

#include "ctest.h"

void
run_all_tests(size_t count, struct test *tests, int argc, char *argv[])
{
	/*
	 * If no tests have been specified at the command line, run them all.
	 */
	if (argc == 1) {
		printf("1..%zu\n", count);

		for (size_t i = 0; i < count; i++)
			execute(i + 1, tests + i);
		return;
	}

	/*
	 * Otherwise, run only the specified tests.
	 */
	printf("1..%d\n", argc - 1);
	for (int i = 1; i < argc; i++)
	{
		int found = 0;
		for (size_t j = 0; j < count; j++) {
			if (strncmp(argv[i], tests[j].t_name,
			    strlen(argv[i])) == 0) {
				found = 1;
				execute(i, tests + j);
				break;
			}
		}

		if (found == 0)
			errx(-1, "No such test '%s'", argv[i]);
	}
}

int
execute(int id, struct test *t) {
	int result;

	pid_t pid = fork();
	if (pid < 0)
		err(-1, "fork");
	if (pid) {
		/* Parent: wait for result from child. */
		int status;
		while (waitpid(pid, &status, 0) != pid) {}
		if (WIFEXITED(status))
			result = WEXITSTATUS(status);
		else
			result = FAILED;
	} else {
		/* Child process: run the test. */
		exit(t->t_run());
	}

	printf("%s %d - %s\n",
		(result == PASSED) ? "ok" : "not ok",
		id, t->t_name);

	return (result);
}

