#include "libft.h"

void	ft_lstclear(t_env **env)
{
	t_env	*current;
	t_env	*temp;

	if (!env)
		return ;
	current = *env;
	while (current)
	{
		temp = current->next;
		ft_lstdelone(current);
		current = temp;
	}
	*env = NULL;
}
