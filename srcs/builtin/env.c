#include "minishell.h"

/*
** Prints out every environment variable.
**
** @param	t_env *env		The pointer to the head of the environment variables linked list;
** @return	int				1 for success and 0 for failure.
*/
int	ft_env(t_env *env)
{
	while (env)
	{
		ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	return (1);
}
