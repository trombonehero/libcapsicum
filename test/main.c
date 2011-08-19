#include <stdio.h>

#include "tests.h"

struct test all_tests[] = {
	TEST_INIT(fdlist),
};
int test_count = sizeof(all_tests) / sizeof(struct test);
	
int
main(int argc, char *argv[])
{
	int i = argc;

	run_all_tests(test_count, all_tests, argc, argv);

	return 0;
}
