#include "minishell.h"

/*
** Sets the OLDPWD environment variable.
**
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	int					1 for success and 0 for failure.
*/
int	set_old_pwd(t_env *env)
{
	char	*wd_path;
	char	*old_pwd_path;

	wd_path = getcwd(NULL, 1024);
	if (!wd_path)
		return (0);
	old_pwd_path = ft_strjoin("OLDPWD=", wd_path);
	if (!is_in_env(env, old_pwd_path))
		add_env_var(&env, old_pwd_path);
	else
		set_env_var(env, old_pwd_path);
	free(wd_path); // might not need to free
	free(old_pwd_path);
	return (1);
}

/*
** Gets the path of a specific environment variable.
**
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	int					The path of the specified environment variable.
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
			while (env->content[len])
			{
				path[i] = env->content[len];
				i++;
				len++;
			}
			path[i] = '\0';
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

/*
** Changes to the home directory.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	int					1 for success and 0 for failure.
*/
int	go_to_hwd(t_env *env)
{
	char	*path;

	path = get_env_path(env, "HOME");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (0);
	}
	set_old_pwd(env);
	chdir(path);
	free(path);
	return (1);
}

/*
** Changes to the previous directory.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	int					1 for success and 0 for failure.
*/
int	go_to_pwd(t_env *env)
{
	char	*path;

	path = get_env_path(env, "OLDPWD");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (0);
	}
	set_old_pwd(env);
	chdir(path);
	free(path);
	return (1);
}

int	print_cd_error(char *arg)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(arg, 2);
	return (0);
}

/*
** Changes the current directory.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	int					1 for success and 0 for failure.
*/
int	ft_cd(int argc, char **argv, t_env *env)
{
	int	status;

	if (argc > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (0);
	}
	if (!argv[1] || !ft_strncmp(argv[1], "~", ft_strlen(argv[1])))
		return (go_to_hwd(env));
	if (!ft_strncmp(argv[1], "-", ft_strlen(argv[1])))
		return (go_to_pwd(env));
	else
	{
		set_old_pwd(env);
		status = chdir(argv[1]);
		if (status != 0)
			return (print_cd_error(argv[1]));
	}
	return (1);
}
