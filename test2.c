#include <unistd.h>
#include <stdio.h>
int	main()
{
	char	line[1000];

	read(STDIN_FILENO, line, 1000);
	printf("%s\n", line);
	return (0);
}
