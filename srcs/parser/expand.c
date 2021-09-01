/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:39:34 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:39:34 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Attempts to expand and replace the token string for $?
** 
** @param t_mini *mini		The mini struct
** @param t_token *curr	The current token struct
** @param int i			The current token string index
** @return int res			1 if $? found and replaced and 0 otherwise
*/
static int	expand_ret_val(t_mini *mini, t_token *curr, int *i)
{
	char	*temp;
	char	*ret_status;

	if (curr->str[*i + 1] == '?')
	{
		ret_status = ft_itoa(mini->exit_status_code);
		temp = ft_strrepl(curr->str, ret_status, *i, *i + 2);
		free(curr->str);
		free(ret_status);
		curr->str = temp;
		*i = *i + 1;
		return (1);
	}
	return (0);
}

/*
** Searches for all env vars in a token and expands it
**
** @param t_mini *mini		The mini struct
** @param t_token *curr	The current token
**
** @return void
*/
static void	expand_token(t_mini *mini, t_token *curr)
{
	int		s_idx;
	int		e_idx;
	int		i;

	i = 0;
	while (i < (int)ft_strlen(curr->str) && curr->str[i])
	{
		if (curr->str[i] == '$')
		{
			if (expand_ret_val(mini, curr, &i))
				continue ;
			if (replace_tokenstr_bs(curr, i))
				continue ;
			s_idx = i;
			e_idx = i + 1;
			while (curr->str[e_idx] && ft_isalnum(curr->str[e_idx]))
				e_idx++;
			replace_tokenstr(mini, curr, s_idx, e_idx);
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
