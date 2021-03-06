/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:47:58 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:47:58 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles sigint signals
**
** @param int	pid		The pid passed in by signal()
** @return void
*/
void	handle_sigint(int pid)
{
	(void) pid;
	g_global.sigint = 1;
	if (g_global.in_fork)
		printf("\n");
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
** Handles sigquit signals
**
** @param int	pid		The pid passed in by signal()
** @return void
** TODO : executable implementation
*/
void	handle_sigquit(int pid)
{
	(void) pid;
	return ;
}

/*
** Handles sigstop signals
**
** @param int	pid		The pid passed in by signal()
** @return void
** TODO : executable implementation
*/
void	handle_sigstop(int pid)
{
	(void) pid;
	printf("\n");
	exit(pid);
}
