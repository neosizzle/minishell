#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int argc, char *argv[])
{
	char *buf;

	buf = readline("?");

	write(STDOUT_FILENO, "====", 5);
	write(STDOUT_FILENO, buf, 10);

	write(STDOUT_FILENO, "\n", 1);
	_exit(EXIT_SUCCESS);
}