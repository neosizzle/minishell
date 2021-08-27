#include "minishell.h"

/*
** This function traverses curr and if it sees
** any delims, call helpers seperately
** 
** @param t_mini* mini		The mini struct
** @param t_token** curr	The current token
** @return void
*/
void	handle_delims(t_mini *mini, t_token *curr, t_token *cmd)
{
	if (curr && curr->type == PIPE)
	{
		create_pipe(mini);
		curr = curr->next;
	}
	if (curr && curr->type == HEREDOC)
	{
		char *res = create_heredoc(curr->next->str);
		mini->heredoc = 1;
		mini->heredoc_buff = res;
		curr->next->type = ARG;
		cmd = curr->next->next;
	}
}