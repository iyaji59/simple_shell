#include <stdio.h>
#include <unistd.h>
int main(void)
{
	pid_t my_pid;
	pid_t get_p;
	my_pid = getpid();
	get_p = getppid();
	printf("%u\n", my_pid);
	printf("%u\n", get_p);
}
