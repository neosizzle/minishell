#include "libft.h"

void	ft_lstdelone(t_env *env)
{
	if (!env)
		return ;
	free(env->content);
	free(env);
}
