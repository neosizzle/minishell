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
	printf("Error : %s\n", message);
	exit(-1);
}