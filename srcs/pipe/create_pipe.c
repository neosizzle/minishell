#include "minishell.h"

int	create_pipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];
	int		status;

	g_global.pipe = 1;
	status = pipe(pipefd);
	if (status < 0)
	{
		mini->pipe_read = -1;
		mini->pipe_write = -1;
		return (0);
	}
	mini->pipe_read = pipefd[0];
	mini->pipe_write = pipefd[1];
	return (1);
}
