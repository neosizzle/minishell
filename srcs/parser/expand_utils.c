/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:43:19 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:43:19 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
** Given the token string and the start and end of expansion,
** returns expanded value
**
** @param t_mini *mini	The mini struct
** @param char* str		The full token string
** @param int start		The start index of expansion
** @param int end		The end index of expansion
** @return char* 		The expanded value
*/
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

void	replace_tokenstr(t_mini *mini, t_token *curr, int s_idx, int e_idx)
{
	char	*temp;
	char	*expanded;

	expanded = expand_env(mini, curr->str, s_idx, e_idx);
	temp = ft_strrepl(curr->str, expanded, s_idx, e_idx);
	free(curr->str);
	free(expanded);
	curr->str = temp;
}

int	replace_tokenstr_bs(t_token *curr, int i)
{
	char	*temp;
	char	*left;
	char	*right;

	if (i > 0 && curr->str[i - 1] == '\\')
	{
		left = ft_substr(curr->str, 0, i - 1);
		right = ft_substr(curr->str, i, ft_strlen(curr->str) - i);
		temp = ft_strjoin(left, right);
		free(left);
		free(right);
		free(curr->str);
		curr->str = temp;
		return (1);
	}
	return (0);
}
