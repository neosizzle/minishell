#include "libft.h"

t_env	*ft_lstnew(char *content)
{
	t_env	*el;

	el = (t_env *) malloc(sizeof(t_env));
	if (!el)
		return (NULL);
	el->content = content;
	el->next = NULL;
	return (el);
}
