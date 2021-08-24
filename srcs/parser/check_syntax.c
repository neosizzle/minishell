#include "minishell.h"

/*
** Checks for unclosed quotes in string
**
** @param	char 	*buff	the line buffer;
** @return 	int 	open	non 0 if quote error and 0 if everythings fine
*/
int	bad_quotes(char *buff)
{
	int	i;
	int	open;

	i = -1;
	open = 0;
	while (buff[++i])
	{
		if (i > 0 && buff[i - 1] == '\\')
			;
		else if (open == 0 && buff[i] == '\"')
			open = 1;
		else if (open == 0 && buff[i] == '\'')
			open = 2;
		else if (open == 1 && buff[i] == '\"')
			open = 0;
		else if (open == 2 && buff[i] == '\'')
			open = 0;
	}
	return (open);
}

/*
** Checks for trailing backslashes in a string
**
** @param	char 	*buff	the line buffer;
** @return 	int 	1 if a bad backslah is detected and 0 otherwise
*/
int	bad_bs(char *buff)
{
	int	len;

	len = ft_strlen(buff);
	if (!len)
		return (0);
	if (len == 1 && buff[0] == '\\')
		return (1);
	if (buff[len - 1] == '\\' && buff[len - 2] != '\\')
		return (1);
	return (0);
}