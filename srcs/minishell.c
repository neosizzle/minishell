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
	add_env_var(mini, "PATH=/bin:/usr/bin");
}

/*
** Entry point.
**
** Initializes variables and structs.
** Set up signal handlers.
** Start parsing next line as long as shell is active.
** Add every command entered to history.
** Free the terminal components after each parse.
** If we are handling pipes, reopen STDIN fd using dup2()
** Free variables and structs.
** If exit signal is sent, free mini struct before ending program.
**
** @return int	status code
*/
int	main(int argc, char *argv[])
{
	t_mini	*mini;
	char	*buff;
	char	*cwd;

	if (argc != 1)
		err("Arguments invalid");
	(void)argv;
	mini = init_mini();
	init_signals(mini);
	init_vars(mini);
	signal(SIGQUIT, &handle_sigquit);
	while (!mini->exit)
	{
		printf("stdin: %d stdout: %d isatty: %d\n", STDIN_FILENO, STDOUT_FILENO, isatty(STDOUT_FILENO));
		cwd = getcwd(NULL, 1024);
		ft_strlcat(cwd, "@minishell> ", 1024 + 13);
		signal(SIGINT, &handle_sigint);
		reset_signals();
		g_global.prompt = cwd;
		buff = readline(cwd);
		if (!buff)
			handle_sigstop(69);
		push_history(mini, buff);
		parse(mini, buff);
		if (g_global.pipe)
			dup2(mini->in_fd, 0);
		free_term(cwd, buff);
		reset_std(mini);
	}
	free_mini(mini);
}
