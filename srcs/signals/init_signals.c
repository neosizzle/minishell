#include "minishell.h"

/*
** Initializes the global signal struct with default values
** 
** @param t_mini	*mini		The mini struct
** @return void
*/
void	init_signals(t_mini *mini)
{
	g_signal.sigint = 0;
	g_signal.prompt = 0;
	g_signal.mini = mini;
}

/*
** Resets signals to 0
** 
** @param void
** @return void
*/
void	reset_signals(void)
{
	g_signal.sigint = 0;
}