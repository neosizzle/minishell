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
** Sets up fds and pipes for execution
** 
** Gets the env vars,
** Gets the string that needed to be sent,
** Create a pipe with fds stored at hererdoc_fd[]
** Fork a chil process
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
	pid = fork();
	if (pid == 0) // child
	{
		close(heredoc_fd[1]);
		dup2(heredoc_fd[0], STDIN_FILENO);
		execve(path, argv, env_arr);
		close(heredoc_fd[0]);
		exit(0);
	}
	else // parent
	{
		close(heredoc_fd[0]);
		write(heredoc_fd[1], mini->heredoc_buff, ft_strlen(mini->heredoc_buff));
		close(heredoc_fd[1]);
		wait(NULL);
		kill(pid, SIGTERM);
	}
	free_heredoc(env_arr, mini);
	return (69);
}
