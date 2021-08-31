/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:45:16 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:45:16 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//helper func to print tokens for debugging, remove on prod
// static void	print_tokens(t_token *tokens)
// {
// 	t_token	*curr;

// 	curr = tokens;
// 	while (curr)
// 	{
// 		printf("token : |%s| type : %d\n", curr->str, curr->type);
// 		curr = curr->next;
// 	}
// }

/*
** Initializes head and creates new token list
**
** @param	t_mini 	*mini	the mini struct pointer;
** @param	char 	*data	the token string;
** @return t_token 	*res	the ptr to the new token
*/
static t_token	*new_token(t_mini *mini, char *data)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	res->str = ft_strdup(data);
	res->type = get_type(mini, data);
	res->prev = 0;
	res->next = 0;
	return (res);
}

/*
** Adds token to the end of the list
**
** @param	char 	*str	the token string;
** @param	t_mini 	*mini	the mini struct pointer;
** @return void
*/
static void	token_addend(char *data, t_mini *mini)
{
	t_token	*prev;
	t_token	*temp;

	prev = mini->tokens;
	while (prev->next)
		prev = prev->next;
	temp = new_token(mini, data);
	prev->next = temp;
	prev->next->prev = prev;
}

/*
** Parses buff and does stuff
**
** Check for bad quotes and formatting.
** Split the buffer using spaces as deliminators.
** Generate token linked list using split buffer.
** Returns to prompt if there is not any buffer.
** Trim the quotes if any.
** Expand environment variables.
** Check for invalid deliminators
** Executes the buffer.
** Frees the tokens
**
** @param	t_mini *mini	the mini struct ptr;
** @param	char	*buff	the buffer string;
** @return void
** TODO :  \' inhibit all interpretation of a sequence of characters.
*/
void	parse(t_mini *mini, char *buff)
{
	char	**split;
	int		i;
	t_token	*head;

	if (bad_quotes(buff) || bad_bs(buff))
		return ;
	split = ft_split_custom(buff, ' ');
	if (!*split)
	{
		free_arr(split);
		return ;
	}
	head = new_token(mini, *split);
	mini->tokens = head;
	i = 0;
	while (split[++i])
		token_addend(split[i], mini);
	trim(mini);
	expand(mini);
	if (bad_delims(mini, split))
		return ;
	execute(mini);
	mini->cmd = 1;
	free_tokens(mini->tokens);
	free_arr(split);
}
