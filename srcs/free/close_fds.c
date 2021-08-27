#include "minishell.h"

/*
** Closes the redirection and pipe fds.
**
** @param	t_mini *mini		The mini struct;
** @return	void
*/
void	close_fds(t_mini *mini)
{
	close(mini->pipe_read);
	close(mini->pipe_write);
	close(mini->redir_in);
	close(mini->redir_out);
}
