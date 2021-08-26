#include "minishell.h"

/*
** This function traverses curr and if it sees
** any delims, call helpers seperately
** 
** @param t_mini* mini		The mini struct
** @param t_token** curr	The current token
** @return void
*/
void	handle_delims(t_mini *mini, t_token *curr)
{
	if (curr && (curr)->type == PIPE)
	{
		create_pipe(mini);
		curr = curr->next;
	}
}