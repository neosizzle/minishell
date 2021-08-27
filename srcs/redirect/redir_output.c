#include "minishell.h"

/*
** Remaps standard output to a new fd.
**
** @param	t_mini *mini		The mini struct;
** @param	t_token *token		The token struct;
** @return	int					1 for success and 0 for failure.
*/
int	redir_output(t_mini *mini, t_token *token, int type)
{
	if (mini->redir_out != -1)
		close(mini->redir_out);
	if (type == TRUNC)
		mini->redir_out = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (type == APPEND)
		mini->redir_out = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->redir_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (0);
	}
	dup2(mini->redir_out, STDOUT_FILENO);
	return (1);
}
