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

static char	*expand_env(t_mini *mini, char *str, int start, int end)
{
	char	*var_name;
	char	*var_str;
	char	*var_val;

	var_name = ft_substr(str, start + 1, end - 1 - start);
	var_str = get_env_var(mini, var_name);
	if (!var_str)
	{
		free(var_name);
		var_val = ft_strdup("");
		return (var_val);
	}
	var_val = get_var_val(var_str);
	free(var_name);
	return (var_val);
}

/*
** Searches for all env vars in a token and expands it
** 
** @param t_mini *mini		The mini struct
** @param t_token *curr	The current token
** 
** @return void
** TODO, backslash cancelling and mem leaks
*/
static void	expand_token(t_mini *mini, t_token *curr)
{
	int		s_idx;
	int		e_idx;
	int		i;
	char	*temp;
	char	*expanded;

	i = 0;
	while (i < ft_strlen(curr->str) && curr->str[i])
	{
		if (curr->str[i] == '$')
		{
			if (i > 0 && curr->str[i - 1] == '\\')
			{
				temp = ft_substr(curr->str, 1, ft_strlen(curr->str) - 1);
				free(curr->str);
				curr->str = temp;
				continue ;
			}
			s_idx = i;
			e_idx = i + 1;
			while (curr->str[e_idx] && ft_isalnum(curr->str[e_idx]))
				e_idx++;
			expanded =  expand_env(mini, curr->str, s_idx, e_idx);
			temp = ft_strrepl(curr->str, expanded, s_idx, e_idx);
			free(curr->str);
			free(expanded);
			curr->str = temp;
			i = e_idx;
		}
		else
			i++;
	}
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

	curr = mini->tokens;
	while (curr)
	{
		if (!g_global.quote)
			expand_token(mini, curr);
		curr = curr->next;
	}
}