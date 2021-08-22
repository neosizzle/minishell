#include "minishell.h"

/*
** Returns the size of the name of an environment variable.
**
** @param	char	*var		The environment variable;
** @return	int				The size of the name of the environment variable.
*/
int	get_env_var_name_size(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

/*
** Sets an existing environment variable in the linked list to a new value.
**
** @param	char	*var		The new environment variable;
** @return	int				The size of the name of the environment variable.
*/
int	set_env_var(t_env *env, char *var)
{
	while (env)
	{
		if (!ft_strncmp(env->content, var, get_env_var_name_size(env->content)))
		{
			free(env->content);
			env->content = ft_strdup(var);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

/*
** Adds an environment variable to the linked list.
**
** @param	t_env	**env		The double pointer to the head of the environment variable linked list;
** @param	char	*var		The environment variable;
** @return	int				1 for success and 0 for failure.
*/
int	add_env_var(t_env **env, char *var)
{
	t_env	*new;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->content = ft_strdup(var);
	new->next = NULL;
	if (!(*env))
		*env = new;
	while (*env && (*env)->next)
		*env = (*env)->next;
	(*env)->next = new;
	return (1);
}

/*
** Removes an environment variable to the linked list.
**
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @param	char	*var		The environment variable;
** @return	int				1 for success and 0 for failure.
*/
int	remove_env_var(t_env *env, char *var)
{
	t_env	*temp;

	if (!ft_strncmp(env->content, var, get_env_var_name_size(env->content)))
	{
		temp = env;
		if (env->next)
			env = env->next;
		ft_lstdelone(temp);
		return (1);
	}
	while (env && env->next)
	{
		if (!ft_strncmp(env->next->content, var, get_env_var_name_size(env->next->content)))
		{
			temp = env->next;
			ft_lstdelone(temp);
			env->next = env->next->next;
			return (1);
		}
	}
	return (0);
}

/*
** Gets an environment variable from the linked list.
**
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @param	char	*var_name	The name of the environment variable;
** @return	char*				The environment variable.
*/
char	*get_env_var(t_env *env, char *var_name)
{
	while (env)
	{
		if (!ft_strncmp(var_name, env->content, ft_strlen(var_name)))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
