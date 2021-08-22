#include "libft.h"

void	ft_lstiter(t_env *env, void (*f)(void *))
{
	if (!f)
		return ;
	while (env)
	{
		(*f)(env->content);
		env = env->next;
	}
}
