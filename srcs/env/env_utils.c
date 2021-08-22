#include "minishell.h"

int	cmp_env_vars(const char *s1, const char *s2)
{
	size_t	offset;

	offset = 0;
	while (s1[offset] && (s1[offset] == s2[offset]))
		offset++;
	return ((unsigned char) s1[offset] - (unsigned char) s2[offset]);
}

t_env	*get_sorted_env_vars(t_env **env)
{
	t_env	*head;
	t_env	*cur;
	char	*cur_content;
	int		unsorted;

	head = ft_lstmap(env);
	if (!(*env))
		return ;
	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		cur = head;
		while (cur->next)
		{
			if (cmp_env_vars(cur->content, cur->next->content) > 0)
			{
				unsorted = 1;
				cur_content = cur->content;
				cur->content = cur->next->content;
				cur->next->content = cur_content;
			}
			cur = cur->next;
		}
	}
	return (head);
}
