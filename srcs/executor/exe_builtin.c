#include "minishell.h"

/*
** Given a command string and its args, execute the function appropriately
**
** @param t_mini *mini	The mini struct.
** @param char *cmd		The command to be executed.
** @param char **args 	The argument string array.
*/
int	exe_builtin(t_mini *mini, char *cmd, char **args)
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
