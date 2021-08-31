/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:37:56 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:37:56 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
