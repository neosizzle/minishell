#include "minishell.h"

/*
** Launches an executable from a relative or absolute path.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	int					The exit status code.
*/
int	ft_exe_path(int argc, char **argv, t_mini *mini)
{
	int		status_code;

	status_code = launch_exe(argv[0], argv, mini);
	return (status_code);
}
