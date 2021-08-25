#include "minishell.h"

/*
** Given a command string and its args, execute the function appropriately
**
** @param t_mini *mini	The mini struct.
** @param char *cmd		The command to be executed.
** @param char **args 	The argument string array.
*/
void	exe_builtin(t_mini *mini, char *cmd, char **args)
{
	int	argc;

	if (mini->pipe_read != -1 || mini->pipe_write != -1)
		return ;
	argc = get_argc(args);
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(argc, args);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(argc, args, mini);
	else if (!ft_strcmp(cmd, "env"))
		ft_env(mini);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(argc, args, mini);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(argc, args, mini);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(argc, args, mini);
	else if (!ft_strcmp(cmd, "history"))
		print_history(mini);
}
