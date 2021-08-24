#include "minishell.h"

/*
** Unsets the specified environment variable and frees its memory.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_mini *mini		The mini struct;
** @return	int					1 for success and 0 for failure.
*/
int	ft_unset(int argc, char **argv, t_mini *mini)
{
	if (!argv[1])
		return (1);
	remove_env_var(mini, argv[1]);
	return (1);
}
