#include "minishell.h"

/*
** Function to detect builtin commands
** (echo cd pwd export unset env exit)
** 
** @param char		*token 	the token string
** @return int		1 if builtin 0 if not not
*/
static int	is_builtin(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (!ft_strncmp(token, "echo", len)
		|| !ft_strncmp(token, "cd", len)
		|| !ft_strncmp(token, "pwd", len)
		|| !ft_strncmp(token, "export", len)
		|| !ft_strncmp(token, "unset", len)
		|| !ft_strncmp(token, "env", len)
		|| !ft_strncmp(token, "ext", len))
		return (1);
	return (0);
}

/*
** Function to detect delims (pipes, redirects, etc)
** and returns the delim macro if found
** 
** @param char		*token 	the token string
** @return int		the delim type macro or 0 if not delim
** TODO : edgecases for this to test
*/
static int	is_delimiter(char *token)
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
	if (is_delimiter(token))
	{
		mini->cmd = 1;
		return (is_delimiter(token));
	}
	if (!mini->cmd)
		return (ARG);
	else
	{
		mini->cmd = 0;
		if (is_builtin(token))
			return (CMD_BUILTIN);
		else
			return (CMD_EXE);
	}
}