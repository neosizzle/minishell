#include "libft.h"

void	ft_lstadd_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!env)
		return ;
	if (*env)
	{
		last = ft_lstlast(*env);
		last->next = new;
	}
	else
		*env = new;
}
