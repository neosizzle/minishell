#include "minishell.h"

/*
** Checks whether an environment variable is present.
**
** @param	t_mini *mini		The mini struct;
** @param	char	*var		The environment variable;
** @return	int					1 for valid and 0 for invalid.
*/
int	is_in_env(t_mini *mini, char *var)
{
	t_env *cur;

	if (!mini->envs)
		return (0);
	cur = mini->envs;
	while (cur)
	{
		if (!ft_strncmp(cur->content, var, ft_strlen(var))) // REPLACE
			return (1);
		cur = cur->next;
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
