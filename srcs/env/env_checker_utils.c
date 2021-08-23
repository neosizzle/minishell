#include "minishell.h"

/*
** Checks whether an environment variable is present.
**
** @param	t_env	*env		The pointer to the head of the environment variables linked list;
** @param	char	*var		The environment variable;
** @return	int					1 for valid and 0 for invalid.
*/
int	is_in_env(t_env *env, char *var)
{
	while (env)
	{
		if (!ft_strncmp(env->content, var, ft_strlen(var))) // REPLACE
			return (1);
		env = env->next;
	}
	return (0);
}

/*
** Checks whether an environment variable is valid.
**
** @param	char	*var		The environment variable;
** @return	int					1 for valid and 0 for invalid.
*/
int	is_valid_env_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalpha(var[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
