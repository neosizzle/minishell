/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:37:54 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:37:54 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_token	*temp;

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
** Frees history linked list
** 
** @param	t_history *head	the history head ptr;
** @return void
*/
void	free_history(t_history *head)
{
	t_history	*temp;

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
	if (mini->history)
		free_history(mini->history);
	if (mini->heredoc_buff)
		free(mini->heredoc_buff);
	free(mini);
}
