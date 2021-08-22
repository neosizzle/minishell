#include "minishell.h"

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