#include "jng.h"

/*
** Frees env linked list
** 
** @param	t_env *head	the env head ptr;
** @return void
*/
void	free_envs(t_env *head)
{
	t_env *curr;
	t_env *prev;

	prev = head;
	curr = head->next;
	if (!curr)
	{
		free(head->content);
		free(head);
		return ;
	}
	while (curr)
	{
		free(prev->content);
		free(prev);
		prev = curr;
		curr = curr->next;
	}
}


/*
** Frees token linked list
** 
** @param	t_token *head	the token head ptr;
** @return void
*/
void	free_tokens(t_token *head)
{
	t_token *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
		temp = head;
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
	if (mini->envs)
		free_envs(mini->envs);
	free(mini);
}