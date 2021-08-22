#include "jng.h"

/*
Function to detect delims (pipes, redirects, etc)
and returns the delim macro if found

@param t_mini 	*mini 	the mini struct pointer
@param char		*token 	the token string
@return int		the delim type macro or 0 if not delim
TODO : edgecases for this to test
*/
static int	is_delimiter(t_mini *mini, char *token)
{
	int	len;

	len = ft_strlen(token);
	if (!ft_strncmp(token, ">", len))
		return (TRUNC);
	if (!ft_strncmp(token, ">>", len))
		return (APPEND);
	if (!ft_strncmp(token, "<", len))
		return (INPUT);
	if (!ft_strncmp(token, "<<", len))
		return (HEREDOC);
	if (!ft_strncmp(token, "|", len))
		return (PIPE);
	if (!ft_strncmp(token, "&&", len))
		return (AND);
	if (!ft_strncmp(token, "||", len))
		return (OR);
	return (0);
}

/*
Function to get the token type

@param t_mini	*mini 	the mini struct pointer
@param char		*token	 the token string
@return int		the token type macro
*/
int	get_type(t_mini *mini, char *token)
{
	if (token[0] == ' ')
		return (EMPTY);
	if (is_delimiter(mini, token))
	{
		mini->cmd = 1;
		return (is_delimiter(mini, token));
	}
	if (!mini->cmd)
		return (ARG);
	else
	{
		mini->cmd = 0;
		return (CMD);
	}
}