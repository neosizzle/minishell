#include "minishell.h"

/*
** Execute an executable file
**
** @param t_mini	*mini		The mini struct
** @param char		*cmd		The cmd to be executed
** @param char		**args		The cmd arguments
** @return void
*/
int	exe_executable(t_mini *mini, char *cmd, char **args)
{
	int argc;
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
