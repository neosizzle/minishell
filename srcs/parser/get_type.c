/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:43:56 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:43:56 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!ft_strcmp(token, "echo")
		|| !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "export")
		|| !ft_strcmp(token, "unset")
		|| !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "exit")
		|| !ft_strcmp(token, "history"))
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
	if (!ft_strcmp(token, ">"))
		return (TRUNC);
	if (!ft_strcmp(token, ">>"))
		return (APPEND);
	if (!ft_strcmp(token, "<"))
		return (INPUT);
	if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	if (!ft_strcmp(token, "&&"))
		return (AND);
	if (!ft_strcmp(token, "||"))
		return (OR);
	if (!ft_strcmp(token, ";"))
		return (SEMI);
	return (0);
}

/*
** Function to get the token type
** 
** @param t_mini	*mini 	the mini struct pointer
** @param char		*token	 the token string
** @return int		the token type macro
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
