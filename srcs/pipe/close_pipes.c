#include "minishell.h"

void	close_write_pipe(t_mini *mini)
{
	close(mini->pipe_write);
	mini->pipe_write = -1;
}

void	close_read_pipe(t_mini *mini)
{
	close(mini->pipe_read);
	mini->pipe_read = -1;
}
