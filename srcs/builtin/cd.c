#include "minishell.h"

/*
** Removes oldpwd from env vars
** 
** @param t_mini *mini	The mini struct
** @return void
*/
static void	remove_oldpwd(t_mini *mini)
{
	char	*old_pwd_var;
	char	*old_pwd;

	old_pwd_var = get_env_var(mini, "OLDPWD");
	if (!old_pwd_var)
		return ;
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_var);
	remove_env_var(mini, old_pwd);
	free(old_pwd);
}

/*
** Sets the OLDPWD environment variable.
**
** @param	t_mini *mini		The mini struct;
** @return	int					The status code.
*/
int	set_old_pwd(t_mini *mini)
{
	char	*wd_path;
	char	*old_pwd_path;

	wd_path = getcwd(NULL, 1024);
	if (!wd_path)
		return (0);
	old_pwd_path = ft_strjoin("OLDPWD=", wd_path);
	if (!is_in_env(mini, old_pwd_path))
		add_env_var(mini, old_pwd_path);
	else
		set_env_var(mini, old_pwd_path);
	free(wd_path);
	free(old_pwd_path);
	return (1);
}

/*
** Changes to the home directory.
**
** @param	t_mini *mini		The mini struct;
** @return	int					The status code.
*/
int	go_to_hwd(t_mini *mini)
{
	char	*path;

	path = get_env_path(mini->envs, "HOME");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	remove_oldpwd(mini);
	set_old_pwd(mini);
	chdir(path);
	free(path);
	return (0);
}

/*
** Changes to the previous directory.
**
** @param	t_mini *mini		The mini struct;
** @return	int					The status code.
*/
int	go_to_pwd(t_mini *mini)
{
	char	*path;

	path = get_env_path(mini->envs, "OLDPWD");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	remove_oldpwd(mini);
	set_old_pwd(mini);
	chdir(path);
	free(path);
	return (0);
}

/*
** Changes the current directory.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_mini *mini		The mini struct;
** @return	int					The status code.
*/
int	ft_cd(int argc, char **argv, t_mini *mini)
{
	int		status;

	if (argc > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (!argv[1] || !ft_strcmp(argv[1], "~"))
		return (go_to_hwd(mini));
	if (!ft_strcmp(argv[1], "-"))
		return (go_to_pwd(mini));
	else
	{
		remove_oldpwd(mini);
		set_old_pwd(mini);
		status = chdir(argv[1]);
		if (status != 0)
			return (print_cd_error(argv[1]));
	}
	return (0);
}
