#include "minishell.h"

/*
** Prints out every environment variable.
**
** @param	t_mini *mini	The mini struct;
** @return	int				The status code.
*/
int	ft_env(t_mini *mini)
{
	t_env	*cur;

	cur = mini->envs;
	while (cur)
	{
		ft_putendl_fd(cur->content, 1);
		cur = cur->next;
	}
	return (0);
}
