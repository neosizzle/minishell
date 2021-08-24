#include "minishell.h"

/*
Adds history to history linkedlist in mini struct.

@param t_mini	*mini		The mini struct 
@param char		*buff		The cmd string
@return void
*/
void	push_history(t_mini *mini, char *buff)
{
	t_history	*temp;
	t_history	*curr;

	temp = (t_history *)malloc(sizeof(t_history));
	temp->str = ft_strdup(buff);
	temp->next = 0;
	if (!mini->history)
	{
		mini->history = temp;
		return ;
	}
	curr = mini->history;
	while (curr->next)
		curr = curr->next;
	curr->next = temp;
}

/*
Prints history given the mini struct

@param t_mini	*mini		The mini struct 
@return void
*/
void	print_history(t_mini *mini)
{
	int			i;
	t_history *curr;

	curr = mini->history;
	i = 0;
	while (curr)
	{
		printf("%d. %s\n", i++, curr->str);
		curr = curr->next;
	}
}