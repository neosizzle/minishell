#include "minishell.h"

static void	get_e_p_helper(t_env *env, char *path, int *i, int *len)
{
	int	res_len;
	int	res_i;

	res_len = *len;
	res_i = *i;
	while (env->content[res_len + 1])
	{
		path[res_i] = env->content[res_len + 1];
		res_i++;
		res_len++;
	}
	*i = res_i;
	*len = res_len;
}

/*
** Gets the path of a specific environment variable.
**
** @param	t_env	*env	The pointer to the head of the env var linked list;
** @return	char*			The path of the specified environment variable.
*/
char	*get_env_path(t_env *env, char *var)
{
	char	*path;
	int		len;
	int		size;
	int		i;

	len = get_env_var_name_size(var);
	while (env)
	{
		size = ft_strlen(env->content) - len;
		if (!ft_strncmp(env->content, var, len))
		{
			path = (char *) malloc(sizeof(char) * (size + 1));
			if (!path)
				return (NULL);
			i = 0;
			get_e_p_helper(env, path, &i, &len);
			path[i] = '\0';
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

int	print_cd_error(char *arg)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(arg, 2);
	return (1);
}
