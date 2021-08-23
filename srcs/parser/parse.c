#include "minishell.h"

/*
** Checks for unclosed quotes in string
**
** @param	char 	*buff	the line buffer;
** @return 	int 	open	non 0 if quote error and 0 if everythings fine
*/
static int	bad_quotes(char *buff)
{
	int	i;
	int	open;

	i = -1;
	open = 0;
	while (buff[++i])
	{
		if (open == 0 && buff[i] == '\"')
			open = 1;
		else if (open == 0 && buff[i] == '\'')
			open = 2;
		else if (open == 1 && buff[i] == '\"')
			open = 0;
		else if (open == 2 && buff[i] == '\'')
			open = 0;
	}
	return (open);
}

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
	res->type = get_type(mini, data);
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
** Check for bad quotes and formatting.
** Split the buffer using spaces as deliminators.
** Generate token linked list using split buffer.
** Trim the quotes if any.
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
	//t_token *curr;

	if (bad_quotes(buff))
	{
		err_noexit("Bad quotes");
		return ;
	}
	split = ft_split_custom(buff , ' ');
	if (!*split)
		return ;
	head = new_token(mini, *split);
	mini->tokens = head;
	//curr = head;
	while (*(++split))
		token_addend(*split, mini);
	trim_quotes(mini);
	// while (curr)
	// {
	// 	printf("Curr token : %s, type : %d\n", curr->str, curr->type);
	// 	curr = curr->next;
	// }
	//execute tokens
	execute(mini);
	mini->cmd = 1;
	free_tokens(mini->tokens);
}
