#include "libft.h"

t_env	*ft_lstmap(t_env *env)
{
	t_env	*head;
	t_env	*new;

	if (!env)
		return (NULL);
	head = NULL;
	while (env)
	{
		new = ft_lstnew(env->content);
		if (!new)
		{
			ft_lstclear(&head);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		env = env->next;
	}
	return (head);
}
