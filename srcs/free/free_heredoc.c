/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:37:49 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:37:49 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees heredoc components and resets heredoc state
** 
** @param char **env_arr	the environment variables
** @param t_mini *mini		the mini struct
** @return void
*/
void	free_heredoc(char **env_arr, t_mini *mini)
{
	free_arr(env_arr);
	free(mini->heredoc_buff);
	mini->heredoc = 0;
	mini->heredoc_buff = 0;
}
