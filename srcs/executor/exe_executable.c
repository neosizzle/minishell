/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:38:03 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:38:03 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints error message in the form of 
** minishell : [path] : [message]
** 
** @param char *path	The path to be printed
** @param char *msg	The message to be printed
** @return void
*/
static void	print_path_err(char *path, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(msg, 2);
}

static int	check_path(char *path)
{
	int	fd;
	int	status_code;
	DIR	*dir;

	fd = open(path, O_RDONLY);
	dir = opendir(path);
	status_code = 126;
	if (ft_strchr(path, '/') == NULL)
		return (128);
	else if (dir != NULL)
	{
		print_path_err(path, ": is a directory");
		status_code = 127;
	}
	else if (fd == -1 && dir == NULL)
	{
		print_path_err(path, ": No such file or directory");
		status_code = 127;
	}
	close(fd);
	closedir(dir);
	return (status_code);
}

/*
** Execute an executable file
**
** @param t_mini	*mini		The mini struct
** @param char		*cmd		The cmd to be executed
** @param char		**args		The cmd arguments
** @return void
*/
int	exe_executable(t_mini *mini, char **args)
{
	int	argc;
	int	status_code;
	int	path_code;

	argc = 0;
	status_code = 0;
	while (args[argc])
		argc++;
	path_code = check_path(args[0]);
	if (path_code == 126)
		status_code = ft_exe_path(argc, args, mini);
	else if (path_code == 127)
		status_code = path_code;
	else if (path_code == 128)
		status_code = ft_exe_env(argc, args, mini);
	return (status_code);
}
