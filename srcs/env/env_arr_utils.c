#include "minishell.h"

/*
** Gets the environment variables in the form of an array of strings.
**
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	char**				The array of strings.
*/
char	**get_env_arr(t_mini *mini)
{
	t_env	*cur;
	char	**arr;
	int		size;
	int		i;

	cur = mini->envs;
	size = ft_lstsize(mini->envs);
	arr = (char **) malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (cur)
	{
		arr[i] = ft_strdup(cur->content);
		i++;
		cur = cur->next;
	}
	arr[i] = NULL;
	return (arr);
}
