#include <stdio.h>
	
int
main(int argc, char *argv[])
{
	int i = argc;
	char *foo = argv[i - 1];
	printf("foo: %s\n", foo);

	return 0;
}
