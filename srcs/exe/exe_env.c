#include "minishell.h"

char	*traverse_dir(char *path, char *exe)
{
	DIR				*dir;
	struct dirent	*dir_contents;
	char			*temp;
	char			*exe_path;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	dir_contents = readdir(dir);
	while (dir_contents)
	{
		if (!ft_strncmp(dir_contents->d_name, exe, ft_strlen(dir_contents->d_name))) // REPLACE
		{
			temp = ft_strjoin(path, "/");
			exe_path = ft_strjoin(temp, dir_contents->d_name);
			free(temp);
		}
		dir_contents = readdir(dir);
	}
	closedir(dir);
	return (exe_path);
}

/*
** Launches an executable found in the PATH environment variable.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_env	*env		The pointer to the head of the environment variable linked list;
** @return	int					The exit status code.
*/
int	ft_exe_env(int argc, char **argv, t_env *env)
{
	char	*var;
	char	**paths;
	char	*path;
	int		i;
	int		status_code;

	var = get_env_var(env, "PATH");
	paths = ft_split(var, ':');
	path = traverse_dir(paths[0], argv[0]);
	i = 1;
	while (path == NULL)
	{
		path = traverse_dir(paths[i], argv[0]);
		i++;
	}
	if (path == NULL)
		status_code = launch_exe(argv[0], argv, env);
	else
		status_code = launch_exe(path, argv, env);
	free_arr(paths);
	free(path);
	return (status_code);
}
