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

/*
** Launches an executable from the specified path argument.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_mini *mini		The mini struct;
** @return	int					The exit status code.
*/
int	launch_exe(char *path, char **argv, t_mini *mini)
{
	pid_t	pid;
	char	**env_arr;
	int		status_code;

	pid = fork();
	g_signal.in_fork = 1;
	if (pid == 0)
	{
		if (mini->pipe_write != -1)
		{
			close(mini->pipe_read);
			dup2(mini->pipe_write, STDOUT_FILENO);
		}
		env_arr = get_env_arr(mini);
		execve(path, argv, env_arr);
		free_arr(env_arr);
		exit(0);
	}
	else
	{
		if (mini->pipe_read != -1)
		{
			dup2(mini->pipe_read, STDIN_FILENO);
			close(mini->pipe_write);
		}
		waitpid(pid, &status_code, 0);
	}
	return (status_code);
}
