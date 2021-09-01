#include "minishell.h"

/*
** Prints the current working directory.
**
** @return	int		The status code.
*/
int	ft_pwd(void)
{
	char	*wd_path;

	wd_path = getcwd(NULL, 1024);
	if (!wd_path)
	{
		free(wd_path);
		return (1);
	}
	ft_putendl_fd(wd_path, 1);
	free(wd_path);
	return (0);
}
