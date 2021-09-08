#include "minishell.h"

/*
** Remaps standard input to a new fd.
**
** @param	t_mini *mini		The mini struct;
** @param	t_token *token		The token struct;
** @return	int					1 for success and 0 for failure.
*/
int	redir_input(t_mini *mini, t_token *token)
{
	if (mini->heredoc_process_delim)
		return (0);
	if (mini->redir_in != -1)
		close(mini->redir_in);
	mini->redir_in = open(token->str, O_RDONLY, S_IRWXU);
	if (mini->redir_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (0);
	}
	dup2(mini->redir_in, STDIN_FILENO);
	return (1);
}
