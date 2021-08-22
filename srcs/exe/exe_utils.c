#include "minishell.h"

int	print_exe_path_err(char *path)
{
	int	fd;
	DIR *dir;

	fd = open(path, O_RDONLY);
	dir = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && dir != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd == -1 && dir == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	close(fd);
	closedir(dir);
	return (0);
}

int	launch_exe(char *path, char **argv, t_env *env)
{
	pid_t	pid;
	char	**env_arr;
	int		status_code;

	pid = fork();
	if (pid == 0)
	{
		env_arr = get_env_arr(env);
		execve(path, argv, env_arr);
		free_arr(env_arr);
		exit(0);
	}
	else
		waitpid(pid, &status_code, 0);
	return (status_code);
}