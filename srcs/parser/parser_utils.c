/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:45:54 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:45:54 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Trims the quotes of a string
** 
** @param char	*str	the string to be trimmed
** @return void nothing
*/
static void	trim_quotes(char **str)
{
	int		len;
	char	*temp;

	if (!(**str == '\'' || **str == '\"'))
		return ;
	if (**str == '\'')
		g_global.quote = 1;
	len = ft_strlen(*str);
	temp = ft_substr(*str, 1, len - 2);
	free(*str);
	*str = temp;
}

/*
** Checks for single backslash in token
** If true, replace with null char and return 1
** 
** @param char **combined	The token str
** @return int 			1 if true and 0 if false
*/
static int	single_bs(char **combined)
{
	if (!ft_strcmp(*combined, "\\"))
	{
		free(*combined);
		*combined = ft_strdup(" ");
		return (1);
	}
	return (0);
}

/*
** Joins left and right and write it to combined
** 
** @param char	*left	The left side of the string to be joined
** @param char	*right	The right side of the string to be joined
** @return void nothing
*/
static void	join_combined(char **combined, char *left, char *right)
{
	free(*combined);
	*combined = ft_strjoin(left, right + 1);
	free(left);
	free(right);
}

/*
** Trims the backslashes of a string
** 
** @param char	*str	the string to be trimmed
** @return void nothing
*/
static void	trim_bs(char **str)
{
	int		bs_idx;
	char	*left;
	char	*right;
	char	*combined;

	bs_idx = 0;
	combined = ft_strdup(*str);
	if (single_bs(&combined))
		;
	else
	{
		while (combined[bs_idx])
		{
			if (combined[bs_idx] == '\\' && combined[bs_idx + 1] != '$')
			{
				left = ft_substr(combined, 0, bs_idx);
				right = ft_substr(combined, bs_idx,
						ft_strlen(combined) - bs_idx);
				join_combined(&combined, left, right);
			}
			bs_idx++;
		}
	}
	free(*str);
	*str = combined;
}

/*
** Traverses tokens and trims the quotes as well as backslashes
** 
** @param t_mini *mini	the mini struct pointer
** @return void nothing
*/
void	trim(t_mini *mini)
{
	t_token	*curr;

	curr = mini->tokens;
	while (curr)
	{
		trim_quotes(&curr->str);
		trim_bs(&curr->str);
		curr = curr->next;
	}
}
