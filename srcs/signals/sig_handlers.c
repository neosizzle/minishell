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
	if (g_signal.in_fork)
		printf("\n");
	else
	printf("\n%s", g_signal.prompt);
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