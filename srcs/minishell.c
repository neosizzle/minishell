/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jng <jng@student.42kl.edu>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:48:14 by jng               #+#    #+#             */
/*   Updated: 2021/08/30 09:48:14 by jng              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

/*
** Initializes mini struct.
**
** Mallocs memory for a mini struct.
** Sets all primitive data types to 0.
** (Not sure)Mallocs memory for non primitive data types.
**
** @param void nothing
** @return t_mini* The pointer to new mini struct
*/
static t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	mini->exit = 0;
	mini->cmd = 1;
	mini->tokens = 0;
	mini->envs = NULL;
	mini->history = 0;
	mini->pipe_read = -1;
	mini->pipe_write = -1;
	mini->redir_in = -1;
	mini->redir_out = -1;
	mini->in_fd = dup(0);
	mini->heredoc = 0;
	mini->heredoc_buff = 0;
	mini->stdin_fd = dup(STDIN_FILENO);
	mini->stdout_fd = dup(STDOUT_FILENO);
	mini->exit_status_code = 0;
	mini->heredoc_redir = 0;
	return (mini);
}

/*
** Initializes vars for mini struct.
**
** Assigns default environment vars
**
** @param t_mini*	mini	The mini struct
** @return void
*/
static void	init_vars(t_mini *mini)
{
	char	*path_env;
	char	*home_env;
	char	*term_env;

	path_env = ft_strjoin("PATH=", getenv("PATH"));
	home_env = ft_strjoin("HOME=", getenv("HOME"));
	term_env = ft_strjoin("TERM=", getenv("TERM"));
	add_env_var(mini, path_env);
	add_env_var(mini, home_env);
	add_env_var(mini, term_env);
	free(path_env);
	free(home_env);
	free(term_env);
}

/*
** This function will run a sequence of instructions after a line is get 
** from readline().
** 1. Push line to history
** 2. Parse line
** 3. Free terminal elements
** 4. Reset file descriptors
** 
** @param t_mini *mini		The pointer to the mini struct
** @param char *buff		The line buffer
** @param char *cwd		The current working directory
** @return void
*/
static void	process_line(t_mini *mini, char *buff, char *cwd)
{
	push_history(mini, buff);
	parse(mini, buff);
	free_term(cwd, buff);
	reset_std(mini);
}

/*
** Checks for argc and argv and prints usage if needed
** 
** @param int argc		The argument count
** @param char **argv	The argument vector
** @return void
*/
void	check_usage(int argc, char **argv)
{
	if (argc > 1 || argv[1])
	{
		ft_putendl_fd("Usage : ./minishell", 2);
		exit(1);
	}
}

/*
** Entry point.
**
** 1. Checks for usage.
** 2. Initializes variables and structs.
** 3. Set up signal handlers.
** 4. Start parsing next line as long as shell is active.
** 5. Add every command entered to history.
** 6. Parse and free the terminal components after each parse.
** 7. If we are handling pipes, reopen STDIN fd using dup2()(Dont need)
** 8. Free variables and structs.
** 9. If exit signal is sent, free mini struct before returning status code.
**
** @return int	status code
*/
// if (g_global.pipe)
// 	dup2(mini->in_fd, 0); (pipe fd not closing issue)
int	main(int argc, char *argv[])
{
	t_mini	*mini;
	char	*buff;
	char	*cwd;
	int		stat_code;

	check_usage(argc, argv);
	mini = init_mini();
	init_signals(mini);
	init_vars(mini);
	signal(SIGQUIT, &handle_sigquit);
	while (!mini->exit)
	{
		cwd = getcwd(NULL, 1024);
		ft_strlcat(cwd, "@minishell> ", 1024 + 13);
		signal(SIGINT, &handle_sigint);
		reset_signals();
		g_global.prompt = cwd;
		buff = readline(cwd);
		if (!buff)
			handle_sigstop(69);
		process_line(mini, buff, cwd);
	}
	stat_code = mini->exit_status_code;
	free_mini(mini);
	return (stat_code);
}
