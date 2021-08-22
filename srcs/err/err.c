#include "jng.h"

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