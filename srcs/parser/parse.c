#include "jng.h"

/*
** Initializes head and creates new token list
** 
** @param	t_mini 	*mini	the mini struct pointer;
** @param	char 	*data	the token string;
** @return t_token 	*res	the ptr to the new token
*/
static t_token	*new_token(t_mini *mini, char *data)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	res->str = data;
	res->type = get_type(mini, data);//TODO : find ways to detect the token type
	res->prev = 0;
	res->next = 0;
	return(res);
}

/*
** Adds token to the end of the list
** 
** @param	char 	*str	the token string;
** @param	t_mini 	*mini	the mini struct pointer;
** @return void
*/
static void	token_addend(char *data, t_mini *mini)
{
	t_token *prev;
	t_token	*temp;

	prev = mini->tokens;
	while (prev->next)
		prev = prev->next;
	temp = new_token(mini, data);
	temp->prev = prev;
	prev->next = temp;
}

/*
** Parses buff and does stuff
** 
** @param	t_mini *mini	the mini struct ptr;
** @param	char	*buff	the buffer string;
** @return void
** TODO : handle dquotes and quotes (custom ft_split)
*/
void	parse(t_mini *mini, char *buff)
{
	char **split;
	t_token *head;
	t_token *curr;

	split = ft_split(buff , ' ');
	if (!*split)
		return ;
	head = new_token(mini, *split);
	mini->tokens = head;
	curr = head;
	while (*(++split))
		token_addend(*split, mini);
	while (curr)
	{
		printf("Curr token : %s, type : %d\n", curr->str, curr->type);
		curr = curr->next;
	}
	//execute tokens
	mini->cmd = 1;
}