#include "minishell.h"

/*
** Checks for valid path
**
** @param	char *path			The argument count;
** @return	int					The exit status code.
*/
int	get_err_status_code(char *path)
{
	int	fd;
	int	status_code;
	DIR	*dir;

	fd = open(path, O_RDONLY);
	dir = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd("command not found", 2);
	else if (fd == -1 && dir != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd == -1 && dir == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && dir == NULL))
		status_code = 127;
	else
		status_code = 126;
	close(fd);
	closedir(dir);
	return (status_code);
}

/*
** 1. Gets all the data needed to launch 
** 2. Launches exe
** 3. Exits with status code
** 
** @param t_mini *mini	The mini struct pointer
** @param char *path	The file path
** @param char **argv	The argument vector
** 
** @return void
*/
static void	launch_and_exit(t_mini *mini, char *path, char **argv)
{
	char	**env_arr;
	int		status_code;

	env_arr = get_env_arr(mini);
	execve(path, argv, env_arr);
	free_arr(env_arr);
	status_code = get_err_status_code(path);
	exit(status_code);
}

/*
** Spins up child process and modifies fds before calling builtin functions
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_mini *mini		The mini struct;
** @return	int					The exit status code.
*/
int	launch_exe(char *path, char **argv, t_mini *mini)
{
	pid_t	pid;
	int		status_code;

	pid = fork();
	g_global.in_fork = 1;
	if (pid == 0)
	{
		if (mini->pipe_write != -1)
		{
			close(mini->pipe_read);
			dup2(mini->pipe_write, STDOUT_FILENO);
		}
		launch_and_exit(mini, path, argv);
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
	return (WEXITSTATUS(status_code));
}
