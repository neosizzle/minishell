#include "minishell.h"

/*
** Frees array of strings
** 
** @param char **arr	The array of strings
** @return void
*/
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
