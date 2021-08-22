#include "minishell.h"

/*
** Error throw function. 
** 
** Prints error message and exits program
** 
** @param	char	*message Error message
** @return void
*/
void	err(char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(-1);
}

/*
** Error throw function without exit. 
** 
** Prints error message
** 
** @param	char	*message Error message
** @return void
*/
void	err_noexit(char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}