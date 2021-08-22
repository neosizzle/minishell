#include "jng.h"

/*
** Frees terminal strings on reread
** @param	char *cwd	the working dir string;
** @param	char *buff	the command buffer;
** @return void
*/
void	free_term(char *cwd, char *buff)
{
	free(cwd);
	free(buff);
}