#include "minishell.h"

/*
** Returns the size of the name of an environment variable.
**
** @param	char	*var		The environment variable;
** @return	int				The size of the name of the environment variable.
*/
int	get_env_var_name_size(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

/*
** Sets an existing environment variable in the linked list to a new value.
**
** @param	t_mini *mini		The mini struct;
** @param	char	*var		The new environment variable;
** @return	int				The size of the name of the environment variable.
*/
int	set_env_var(t_mini *mini, char *var)
{
	t_env	*cur;

	cur = mini->envs;
	while (cur)
	{
		if (!ft_strncmp(cur->content, var, get_env_var_name_size(cur->content)))
		{
			free(cur->content);
			cur->content = ft_strdup(var);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

/*
** Adds an environment variable to the linked list.
**
** @param	t_mini *mini		The mini struct;
** @param	char	*var		The environment variable;
** @return	int				1 for success and 0 for failure.
** TODO : Overwrite old env if similar name found
*/
int	add_env_var(t_mini *mini, char *var)
{
	t_env	*new;

	if (is_in_env(mini, var))
		return (0);
	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->content = ft_strdup(var);
	new->next = NULL;
	if (!mini->envs)
		mini->envs = new;
	else
		add_env_back(mini, new);
	return (1);
}

/*
** Removes an environment variable to the linked list.
**
** @param	t_env	*env		The pointer to the head of the env var linked list;
** @param	char	*var		The environment variable;
** @return	int				1 for success and 0 for failure.
*/
int	remove_env_var(t_mini *mini, char *var)
{
	t_env	*cur;
	t_env	*temp;

	if (!mini->envs)
		return (0);
	if (!ft_strncmp(mini->envs->content, var, get_env_var_name_size(mini->envs->content)))
	{
		temp = mini->envs;
		if (mini->envs->next)
			mini->envs = mini->envs->next;
		else
			mini->envs = NULL;
		ft_lstdelone(temp);
		return (1);
	}
	cur = mini->envs;
	while (cur && cur->next)
	{
		if (!ft_strncmp(cur->next->content, var, get_env_var_name_size(cur->next->content)))
		{
			temp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(temp);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

/*
** Gets an environment variable from the linked list.
**
** @param	t_mini *mini		The mini struct;
** @param	char	*var_name	The name of the environment variable;
** @return	char*				The environment variable.
*/
char	*get_env_var(t_mini *mini, char *var_name)
{
	t_env 	*cur;
	char	*content_name;

	cur = mini->envs;
	while (cur)
	{
		content_name = get_env_name(cur->content);
		if (!ft_strcmp(var_name, content_name))
		{
			free(content_name);
			return (cur->content);
		}
		free(content_name);
		cur = cur->next;
	}
	return (NULL);
}
