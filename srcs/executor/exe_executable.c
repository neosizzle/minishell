/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:38:03 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:38:03 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Execute an executable file
**
** @param t_mini	*mini		The mini struct
** @param char		*cmd		The cmd to be executed
** @param char		**args		The cmd arguments
** @return void
*/
int	exe_executable(t_mini *mini, char **args)
{
	int	argc;
	int	status_code;

	argc = 0;
	while (args[argc])
		argc++;
	if (ft_exe_path(argc, args, mini) == -1)
		status_code = ft_exe_env(argc, args, mini);
	else
		status_code = ft_exe_env(argc, args, mini);
	return (status_code);
}
