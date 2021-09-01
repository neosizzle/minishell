#include "minishell.h"

/*
** Switches the contentd between two env nodes
** 
** @param t_env *cur	The current node
** @param t_env *next	The node to switch content with
** @return void
*/
static void	switch_contents(t_env *cur, t_env *next)
{
	char	*cur_content;

	cur_content = cur->content;
	cur->content = next->content;
	next->content = cur_content;
}

/*
** Gets a newly created and sorted environment variables linked list.
**
** @param	t_mini *mini		The mini struct;
** @return	t_env*				The sorted environment variables linked list.
*/
t_env	*get_sorted_env_vars(t_mini *mini)
{
	t_env	*head;
	t_env	*cur;
	int		unsorted;

	if (!mini->envs)
		return (NULL);
	head = ft_lstmap(mini->envs);
	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		cur = head;
		while (cur->next)
		{
			if (ft_strcmp(cur->content, cur->next->content) > 0)
			{
				unsorted = 1;
				switch_contents(cur, cur->next);
			}
			cur = cur->next;
		}
	}
	return (head);
}

int	print_env_var_error(char *arg)
{
	ft_putstr_fd("export: not a valid identifier: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

/*
** Prints out every environment variable sorted by alphabetical order.
**
** @param	t_mini *mini		The mini struct;
** @return	int		The status code.
*/
int	print_sorted_env_vars(t_mini *mini)
{
	t_env	*head;
	t_env	*curr;

	head = get_sorted_env_vars(mini);
	curr = head;
	while (curr)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(curr->content, 1);
		curr = curr->next;
	}
	ft_lstclear(&head);
	return (0);
}

/*
** If argument is provided, sets environment variable.
** If not, prints out every environment variable sorted by alphabetical order.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_mini *mini		The mini struct;
** @return	int		The status code.
*/
int	ft_export(int argc, char **argv, t_mini *mini)
{
	int	i;

	i = 1;
	(void)argc;
	if (argv[i])
	{
		if (!is_valid_env_var(argv[i]))
			return (print_env_var_error(argv[i]));
		add_env_var(mini, argv[i]);
	}
	else
		print_sorted_env_vars(mini);
	return (0);
}
