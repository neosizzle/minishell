#include "minishell.h"

//REMOVE IN PROD
//Test function I made to print the args.
static void	print_args(char **args)
{
	if (!args)
	{
		printf("No args\n");
		return ;
	}
	while (*args)
	{
		printf("arg : %s\n", *args);
		args++;
	}
}

/*
** Given a token linked list, it will get the arguments and convert
** into array of strings.
**
** @param t_token *tokens Head of tokens linked list
** @return char **args The resultant string array.
*/
static char	**get_args(t_token	*tokens)
{
	int		i;
	t_token	*curr;
	char	**res;

	i = 0;
	curr = tokens;
	while (curr && curr->type <= ARG)
	{
		++i;
		curr = curr->next;
	}
	if (!i)
		return (0);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	curr = tokens;
	while (curr && curr->type <= ARG)
	{
		res[i++] = ft_strdup(curr->str);
		curr = curr->next;
	}
	res[i] = 0;
	return (res);
}

/*
** Given a command and its args, execute the function appropriately
**
** @param t_token *cmd		The command to be executed
** @param char **args		The arguments
** @param t_mini *mini		The mini struct
** @return void nothing
*/
static void	execute_cmd(t_token *cmd, char **args, t_mini *mini)
{
	if (cmd->type == CMD_BUILTIN)
		exe_builtin(mini, cmd->str, args);
	if (cmd->type == CMD_EXE)
		exe_executable(mini, cmd->str, args);
}

/*
Given an array of strings, count the number of string in that array

@param char** args	The array of strings
@return int argc The number of strings
*/
int	get_argc(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

/*
** Calls exes based on token with its args if any
**
** Converts token arguments into array of strings.
** Calls function based on builtin or executable
** Move token ptr to nexe non-argument token
**
** @param t_mini	*mini The mini struct ptr
** @return int		status The status code
** TODO : add piping & redirection support and fix seg fault when freeing args
*/
int	execute(t_mini *mini)
{
	t_token	*curr;
	t_token *cmd;
	char	**args;

	curr = mini->tokens;
	while (curr)
	{
		printf("current token: %s\n", curr->str);
		//get args
		cmd = curr;
		args = get_args(cmd);
		curr = curr->next;
		while (curr && curr->type == ARG)
			curr = curr->next;
		if (curr && curr->type == PIPE)
		{
			create_pipe(mini);
			//printf("pipe read: %d write: %d\n", mini->pipe_read, mini->pipe_write);
			curr = curr->next;
		}
		//printf("current cmd: %s\n", cmd->str);
		//print_args(args);
		//execute cmd / change for piping and redir (?)
		execute_cmd(cmd, args, mini);

		//to next non arg token
		// close_read_pipe(mini);
		// close_write_pipe(mini);
		free_arr(args);
	}
	return (0);
}
