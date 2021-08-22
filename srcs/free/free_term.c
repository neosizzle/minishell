#include "jng.h"

/*
** Frees terminal strings on reread
** @param	char *mlx_ptr	the working dir string;
** @param	char *win_ptr	the command buffer;
** @return void
*/
void	free_term(char *cwd, char *buff)
{
	free(cwd);
	free(buff);
}