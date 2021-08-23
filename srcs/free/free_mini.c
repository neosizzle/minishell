#include "jng.h"

/*
** Frees env linked list
**
** @param	t_env *head	the env head ptr;
** @return void
*/
void	free_envs(t_mini *mini)
{
	t_env	*cur;
	t_env	*temp;

	cur = mini->envs;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		free(temp->content);
		free(temp);
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
		free_envs(mini);
	free(mini);
}
