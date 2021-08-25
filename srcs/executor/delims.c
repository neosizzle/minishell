#include "minishell.h"

/*
This function traverses the tokens to finds the next delim

@param t_token *curr	The current token
@return int				1 if delim found and 0 if not
*/
int	has_next_delim(t_token *curr)
{
	int	res;

	res = 0;
	while (curr)
	{
		if (curr->type > ARG)
			return (1);
		curr = curr->next;
	}
	return (0);
}

/*
This function traverses the tokens to finds the next delim

@param t_token *curr	The current token
@return int				1 if delim found and 0 if not
*/
t_token	*get_right_cmd(t_token *curr)
{
	t_token	*res;

	res = curr;
	while (res->next)
	{
		if (res->type > ARG)
			return (res->next);
		res = res->next;
	}
	return (curr);
}