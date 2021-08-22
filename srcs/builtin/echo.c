#include "minishell.h"

/*
** Prints out the arguments passed.
**
** @param	int		argc		the argument count;
** @param	char	**argv		the array of argument strings;
** @return	int					1 for success and 0 for failure.
*/
int	ft_echo(int argc, char **argv)
{
	int	i;
	int	flag;

	if (argc < 2)
		return (0);
	i = 1;
	flag = 0;
	if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != '\0')
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (1);
}
