#include "minishell.h"

/*
** Execute an executable file
** 
** @param t_mini	*mini		The mini struct
** @param char		*cmd		The cmd to be executed
** @param char		**args		The cmd arguments
** @return void
*/
void	exe_executable(t_mini *mini, char *cmd, char **args)
{
	int argc;

	argc = 0;
	while (args[argc])
		argc++;
	//ft_exe_path(argc, args, mini);
	//printf("Code : %d\n", code);
	ft_exe_env(argc, args, mini);
}