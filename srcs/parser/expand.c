#include "minishell.h"

/*
** Given a string in the form of x=y, return y
** 
** @param char* str	The full string
** @return char* 		The extracted value
*/
static char	*get_var_val(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	if (str[i] == '=')
		res = ft_substr(str, i + 1, ft_strlen(str) - i);
	else
		res = 0;
	return (res);
}

/*
** Given a string in the form of $x, return x
** 
** @param char* str	The full string
** @return char* 		The extracted value
*/
static char	*get_var_name(char *str)
{
	char	*res;

	res = ft_substr(str, 1, ft_strlen(str) - 1);
	return (res);
}

/*
** Expands environmental variables into its full form
** 
** @param t_mini *mini	The mini struct
** @return void
*/
void	expand(t_mini *mini)
{
	t_token	*curr;
	char	*temp;
	char	*var_name;

	curr = mini->tokens;
	while (curr)
	{
		if (curr->str[0] == '$')
		{
			var_name = get_var_name(curr->str);
			temp = get_env_var(mini, var_name);
			free(curr->str);
			if (!temp)
				curr->str = ft_strdup("");
			else
				curr->str = get_var_val(temp);
			free(var_name);
		}
		curr = curr->next;
	}
}