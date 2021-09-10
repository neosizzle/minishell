#include "minishell.h"

/*
** Iniitialies heredoc stream
** 
** @param char *delim		The delim to read
** @return char *res		The strings read excluding the delim
*/
char	*create_heredoc(char *delim)
{
	char	*buff;
	char	*res;
	char	*temp;
	int		exit_status;

	exit_status = 0;
	res = ft_strdup("");
	while (!exit_status)
	{
		buff = readline(">");
		if (!buff)
			break ;
		if (!ft_strcmp(buff, delim))
			break ;
		temp = ft_strjoin(res, buff);
		free(res);
		free(buff);
		res = ft_strjoin(temp, "\n");
		free(temp);
	}
	free(buff);
	return (res);
}

/*
** Depending on the delim type, call helper functons to create fd pipes
** 
** @param t_mini *mini	The mini struct
** @return void
*/
static void	handle_hd_delims(t_mini *mini)
{
	int		next_delim;
	t_token	*next;

	next_delim = mini->heredoc_next_delim;
	next = mini->heredoc_next_token;
	if (next_delim == APPEND || next_delim == TRUNC)
		redir_output(mini, next, next_delim);
	if (next_delim == INPUT)
		redir_input(mini, next);
	if (next_delim == PIPE)
		create_pipe(mini);
	mini->heredoc_process_delim = 1;
}

/*
** Initializes child sequence for launching heredoc executable
** 
** @param int heredoc_fd[2]	The heredoc pipe fd pairs
** @param t_mini *mini			The mini struct
** @return void
*/
static void	init_hd_child_sq(int heredoc_fd[2], t_mini *mini)
{
	close(heredoc_fd[1]);
	dup2(heredoc_fd[0], STDIN_FILENO);
	if (mini->pipe_write != -1)
	{
		close(mini->pipe_read);
		dup2(mini->pipe_write, STDOUT_FILENO);
	}
}

/*
** Initializes parent sequence for launching heredoc executable
** 
** @param int heredoc_fd[2]	The heredoc pipe fd pairs
** @param t_mini *mini		The mini struct
** @param int pid			The pid of child process
** @return void
*/
static void	init_hd_parent_sq(int heredoc_fd[2], t_mini *mini, pid_t pid)
{
	close(heredoc_fd[0]);
	write(heredoc_fd[1], mini->heredoc_buff, ft_strlen(mini->heredoc_buff));
	if (mini->pipe_write != -1)
	{
		dup2(mini->pipe_read, STDIN_FILENO);
		close(mini->pipe_write);
	}
	close(heredoc_fd[1]);
	wait(NULL);
	kill(pid, SIGTERM);
}

/*
** Sets up fds and pipes for execution
** 
** Gets the env vars,
** Gets the string that needed to be sent,
** Create a pipe with fds stored at hererdoc_fd[]
** Handle any special delims after the heredoc
** Fork a child process
** 
** In the child:
** Close the WRITE end of the pipe since we reading,
** Duplicate the READ end of the pipe with stdin,
** Execute the binary provided in path,
** Close the READ end after we use it and exit program
** 
** In the parent:
** Close the READ end of the pipe since we writing,
** Write the string to the WRITE end of the pipe so the child can read,
** Close the WRITE end of the pipe after use,
** The child process should finish, but we kill (send EOF) it just incase :)
** 
** Free and return.
** 
** @param t_mini *mini		The mini struct
** @param char *path		The bin path
** @param char **argv		The cmd arguments
** @return int				The return value
*/
int	launch_heredoc(t_mini *mini, char *path, char **argv)
{
	char	**env_arr;
	int		heredoc_fd[2];
	pid_t	pid;

	env_arr = get_env_arr(mini);
	pipe(heredoc_fd);
	handle_hd_delims(mini);
	pid = fork();
	if (pid == 0)
	{
		init_hd_child_sq(heredoc_fd, mini);
		execve(path, argv, env_arr);
		close(heredoc_fd[0]);
		exit(0);
	}
	else
		init_hd_parent_sq(heredoc_fd, mini, pid);
	free_heredoc(env_arr, mini);
	return (0);
}
