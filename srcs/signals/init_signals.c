/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:47:55 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:47:55 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Initializes the global signal struct with default values
** 
** @param t_mini	*mini		The mini struct
** @return void
*/
void	init_signals(t_mini *mini)
{
	g_global.sigint = 0;
	g_global.prompt = 0;
	g_global.in_fork = 0;
	g_global.pipe = 0;
	g_global.quote = 0;
	g_global.mini = mini;
}

/*
** Resets signals to 0
** 
** @param void
** @return void
*/
void	reset_signals(void)
{
	g_global.sigint = 0;
	g_global.in_fork = 0;
	g_global.quote = 0;
}
