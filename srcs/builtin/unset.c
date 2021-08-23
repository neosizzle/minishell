#include "minishell.h"

/*
** Unsets the specified environment variable and frees its memory.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_env	*env		The pointer to the head of the environment variables linked list;
** @return	int					1 for success and 0 for failure.
*/
int	ft_unset(int argc, char **argv, t_env **env)
{
	t_env	*temp;

	if (!argv[1])
		return (1);
	remove_env_var(env, argv[1]);
	return (1);
}
