#include "minishell.h"

/*
** Checks for unclosed quotes in string, 
** If an unclosed quotes is found, print err msg and return 1
**
** @param	char 	*buff	the line buffer;
** @return 	int 	open	non 0 if quote error and 0 if everythings fine
*/
int	bad_quotes(char *buff)
{
	int	i;
	int	open;

	i = -1;
	open = 0;
	while (buff[++i])
	{
		if (i > 0 && buff[i - 1] == '\\')
			;
		else if (open == 0 && buff[i] == '\"')
			open = 1;
		else if (open == 0 && buff[i] == '\'')
			open = 2;
		else if (open == 1 && buff[i] == '\"')
			open = 0;
		else if (open == 2 && buff[i] == '\'')
			open = 0;
	}
	if (!open)
		return (open);
	else
	{
		err_noexit("Unclosed quotes");
		return (open);
	}
}

/*
** Checks for trailing backslashes in a string,
** If an invalid backslash is found, print err msg and return 1
**
** @param	char 	*buff	the line buffer;
** @return 	int 	1 if a bad backslah is detected and 0 otherwise
*/
int	bad_bs(char *buff)
{
	int	len;

	len = ft_strlen(buff);
	if (!len)
		return (0);
	if (len == 1 && buff[0] == '\\')
	{
		err_noexit("Bad backslash");
		return (1);
	}
	if (buff[len - 1] == '\\' && buff[len - 2] != '\\')
	{
		err_noexit("Bad backslash");
		return (1);
	}
	return (0);
}

/*
** Returns 0 if token is not surrounded by cmds or args
**
** @param	t_token	*token	the token struct;
** @return 	int 	0 if bad placement and 1 otherwise
*/
static int	check_placement(t_token *token)
{
	if (!token->next || !token->prev)
		return (0);
	if (token->next->type >= TRUNC || token->prev->type >= TRUNC)
		return (0);
	return (1);
}

/*
** Checks for invalid delimiter placement,
** If invalid delims are found, it will free the tokens
** and the splitted arr and return 1
**
** @param	t_mini	*mini	the mini struct;
** @return 	int 	1 if a bad delim is present and 0 otherwise
*/
int	bad_delims(t_mini *mini, char **split)
{
	t_token	*curr;

	curr = mini->tokens;
	while (curr)
	{
		if (curr->type > ARG && !check_placement(curr))
		{
			err_noexit("Bad delims");
			free_tokens(mini->tokens);
			free_arr(split);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}