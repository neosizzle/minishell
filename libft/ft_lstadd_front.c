#include "libft.h"

void	ft_lstadd_front(t_env **env, t_env *new)
{
	if (!env)
		return ;
	new->next = *env;
	*env = new;
}
