#include "jng.h"

/*
** Frees token linked list
** 
** @param	t_token *head	the token head ptr;
** @return void
*/
void	free_tokens(t_token *head)
{
	t_token *curr;
	t_token *prev;

	prev = head;
	curr = head->next;
	if (!curr)
	{
		free(head->str);
		free(head);
		return ;
	}
	while (curr)
	{
		free(prev->str);
		free(prev);
		prev = curr;
		curr = curr->next;
	}
}

/*
** Frees mini struct as well as its components
** 
** @param	t_mini *mini	the mini struct ptr;
** @return void
*/
void	free_mini(t_mini *mini)
{
	if (mini->tokens)
		free_tokens(mini->tokens);
	free(mini);
}