#include "minishell.h"

/*
** This function traverses the current token and returns the next delim
** pipe, redir etc..
** 
** @param t_token *curr	token pointer
** @return int 			Token type macro
*/
int	get_next_delim(t_token *curr)
{
	t_token	*temp;

	temp = curr->next;
	while (temp)
	{
		if (temp->type < HEREDOC && temp->type > ARG)
			return (temp->type);
		temp = temp->next;
	}
	return (0);
}
