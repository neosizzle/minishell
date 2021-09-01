/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:46:58 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:46:58 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int call_builtin(t_mini *mini, char *cmd, char **args)
{
	int	argc;
	int	status_code;

	argc = get_argc(args);
	if (!ft_strcmp(cmd, "echo"))
		status_code = ft_echo(argc, args);
	else if (!ft_strcmp(cmd, "pwd"))
		status_code = ft_pwd();
	else if (!ft_strcmp(cmd, "cd"))
		status_code = ft_cd(argc, args, mini);
	else if (!ft_strcmp(cmd, "env"))
		status_code = ft_env(mini);
	else if (!ft_strcmp(cmd, "exit"))
		status_code = ft_exit(argc, args, mini);
	else if (!ft_strcmp(cmd, "export"))
		status_code = ft_export(argc, args, mini);
	else if (!ft_strcmp(cmd, "unset"))
		status_code = ft_unset(argc, args, mini);
	else if (!ft_strcmp(cmd, "history"))
		status_code = print_history(mini);
	return (status_code);

}

/*
** Given a command string and its args, execute the function appropriately
**
** @param t_mini *mini	The mini struct.
** @param char *cmd		The command to be executed.
** @param char **args 	The argument string array.
*/
int	exe_builtin(t_mini *mini, char *cmd, char **args)
{
	pid_t	pid;
	int		status_code;

	pid = fork();
	g_global.in_fork = 1;
	if (pid == 0)
	{
		if (mini->pipe_write != -1)
		{
			close(mini->pipe_read);
			dup2(mini->pipe_write, STDOUT_FILENO);
		}
		status_code = call_builtin(mini, cmd, args);
		exit(status_code);
	}
	else
	{
		if (mini->pipe_read != -1)
		{
			dup2(mini->pipe_read, STDIN_FILENO);
			close(mini->pipe_write);
		}
		waitpid(pid, &status_code, 0);
		if (!ft_strcmp(cmd, "exit"))
		{
			mini->exit = 1;
			mini->exit_status_code = WEXITSTATUS(status_code);
		}
	}
	return (status_code);
}
