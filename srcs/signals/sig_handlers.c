#include "minishell.h"

/*
** Handles sigint signals
** 
** @param int	pid		The pid passed in by signal()
** @return void
** TODO : executable implementation
*/
void	handle_sigint(int pid)
{
	(void) pid;
	printf("\n%s", g_signal.prompt);
}
