#include "minishell.h"

void	close_fds(t_mini *mini)
{
	close(mini->pipe_read);
	close(mini->pipe_write);
	close(mini->redir_in);
	close(mini->redir_out);
}
