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
	else if (curr && curr->type == HEREDOC)
	{
		char *res = create_heredoc(curr->next->str);
		mini->heredoc = 1;
		mini->heredoc_buff = res;
		curr->next->type = ARG;
		cmd = curr->next->next;
	}
	else if (curr && curr->type == INPUT)
	{
		curr = curr->next;
		redir_input(mini, curr);
	}
	else if (curr && (curr->type == APPEND || curr->type == TRUNC))
	{
		curr = curr->next;
		redir_output(mini, curr, curr->prev->type);
	}
}