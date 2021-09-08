/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delims.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:38:16 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:38:16 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Handles pipes
**
**@param t_mini *mini 	the mini struct
**@param t_token *curr	The current token
**@return void
*/
static void	handle_pipes(t_mini *mini, t_token *curr)
{
	create_pipe(mini);
	curr = curr->next;
}

/*
**Handles heredocs
**
**@param t_mini *mini 	the mini struct
**@param t_token *curr	The current token
**@param t_token *curr	The comamnd token
**@return void
*/
// only supports 1 heredoc argument (line 45)
static void	handle_heredocs(t_mini *mini, t_token *curr)
{
	mini->heredoc = 1;
	mini->heredoc_buff = create_heredoc(curr->next->str);
	curr->next->type = ARG;
	mini->heredoc_next_delim = get_next_delim(curr);
	if (mini->heredoc_next_delim)
	{
		curr = curr->next->next->next;
		mini->heredoc_next_token = curr;
	}
}

/*
**Handles input redirections
**
**@param t_mini *mini 	the mini struct
**@param t_token *curr	The current token
**@return void
*/
static void	handle_input(t_mini *mini, t_token *curr)
{
	curr = curr->next;
	curr->type = ARG;
	redir_input(mini, curr);
}

/*
**Handles output redirections
**
**@param t_mini *mini 	the mini struct
**@param t_token *curr	The current token
**@return void
*/
static void	handle_output(t_mini *mini, t_token *curr)
{
	curr = curr->next;
	curr->type = ARG;
	redir_output(mini, curr, curr->prev->type);
}

/*
** This function traverses curr and if it sees
** any delims, call helpers seperately
** 
** @param t_mini* mini		The mini struct
** @param t_token** curr	The current token
** @return void
*/
void	handle_delims(t_mini *mini, t_token *curr, t_token *cmd)
{
	if (!cmd)
		return ;
	if (curr && curr->type == PIPE)
		handle_pipes(mini, curr);
	else if (curr && curr->type == HEREDOC)
		handle_heredocs(mini, curr);
	else if (curr && curr->type == INPUT)
		handle_input(mini, curr);
	else if (curr && (curr->type == APPEND || curr->type == TRUNC))
		handle_output(mini, curr);
}
