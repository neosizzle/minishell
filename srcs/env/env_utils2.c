#include "minishell.h"

/*
** This function will extract the env vame from the contents
** and will compare the names
** 
** @param char *s1		The first env content
** @param char *s2		The other env content
** @return int res		The comparison result
*/
//unsafe, might go out of bounds
static int	env_name_cmp(char *s1, char *s2)
{
	char	*s1_name;
	char	*s2_name;
	int		eq_idx;
	int		res;

	eq_idx = 0;
	while (s1[eq_idx] && s1[eq_idx] != '=')
		eq_idx++;
	s1_name = ft_substr(s1, 0, eq_idx);
	eq_idx = 0;
	while (s2[eq_idx] && s2[eq_idx] != '=')
		eq_idx++;
	s2_name = ft_substr(s2, 0, eq_idx);
	res = ft_strcmp(s1_name, s2_name);
	free(s1_name);
	free(s2_name);
	return (res);
}

/*
** This function will go through the env linked list one
** to check for existing names.
** If found, it will overwrite the value with the
** env provided
** If not found, it will simple add it the new env
** to the end of the list
** 
** @param t_mini *mini		The mini struct pointer
** @param t_env *env		The new env to be added
** @return void
*/
void	add_env_back(t_mini *mini, t_env *env)
{
	t_env	*curr;
	int		overwrite;

	overwrite = 0;
	curr = mini->envs;
	while (curr)
	{
		if (!env_name_cmp(curr->content, env->content))
		{
			free(curr->content);
			curr->content = env->content;
			free(env);
			overwrite = 1;
			break ;
		}
		curr = curr->next;
	}
	if (!overwrite)
		ft_lstadd_back(&(mini->envs), env);
}

/*
** Given the env content in the form of x=y, return x
** 
** @param char *str	The env content
** @return char *		THe trimmed result
*/
char	*get_env_name(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] != '=')
		++i;
	res = ft_substr(str, 0, i);
	return (res);
}
