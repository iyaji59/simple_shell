#include <stdio.h>
#include <stdlib.h>
int main(int argc __attribute__((unused)), char *argv[])
{
	int i;
	for (i = 1; argv[i] != NULL; i++)
	{
		printf("args values are: %s\n", argv[i]);
	}
	return (0);
}
