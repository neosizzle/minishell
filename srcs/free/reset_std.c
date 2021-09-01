#include "minishell.h"

/*
** Remaps the standard input and output to the terminal.
**
** @param	t_mini *mini		The mini struct;
** @return	void
*/
void	reset_std(t_mini *mini)
{
	dup2(mini->stdin_fd, STDIN_FILENO);
	dup2(mini->stdout_fd, STDOUT_FILENO);
}
