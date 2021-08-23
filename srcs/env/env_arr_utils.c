#include "minishell.h"

/*
** Gets the environment variables in the form of an array of strings.
**
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	char**				The array of strings.
*/
char	**get_env_arr(t_env *env)
{
	char	**arr;
	int		size;
	int		i;

	size = ft_lstsize(env);
	arr = (char **) malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (env)
	{
		arr[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
