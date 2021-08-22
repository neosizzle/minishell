#include "minishell.h"

/*
** Trims the quotes of a string
** 
** @param char	*str	the string to be trimmed
** @return void nothing
*/
static void	trim(char **str)
{
	int		len;
	char	*temp;

	if (!(**str == '\'' || **str == '\"'))
		return ;
	len = ft_strlen(*str);
	temp = ft_substr(*str, 1, len - 2);
	free(*str);
	*str = temp;
}

/*
** Traverses tokens and trims the quotes
** 
** @param t_mini *mini	the mini struct pointer
** @return void nothing
*/
void	trim_quotes(t_mini *mini)
{
	t_token *curr;

	curr = mini->tokens;
	while (curr)
	{
		trim(&curr->str);
		curr = curr->next;
	}
}