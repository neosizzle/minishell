#include "libft.h"

t_env	*ft_lstlast(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}
