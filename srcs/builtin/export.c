#include "minishell.h"

t_env	*get_sorted_env_vars(t_env *env)
{
	t_env	*head;
	t_env	*cur;
	char	*cur_content;
	int		unsorted;

	head = ft_lstmap(env);
	if (!env)
		return (NULL);
	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		cur = head;
		while (cur->next)
		{
			if (ft_strncmp(cur->content, cur->next->content, ft_strlen(cur->content)) > 0)
			{
				unsorted = 1;
				cur_content = cur->content;
				cur->content = cur->next->content;
				cur->next->content = cur_content;
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
	return (0);
}

int	print_sorted_env_vars(t_env *env)
{
	t_env	*head;

	head = get_sorted_env_vars(env);
	while (head)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(head->content, 1);
		head = head->next;
	}
	ft_lstclear(&head);
}

/*
** If argument is provided, sets environment variable.
** If not, prints out every environment variable sorted by alphabetical order.
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_env	*env		The pointer to the head of the environment variables linked list;
** @return	int					1 for success and 0 for failure.
*/
int	ft_export(int argc, char **argv, t_env **env)
{
	int i;

	i = 1;
	if (argv[i])
	{
		if (!is_valid_env_var(argv[i]))
			return (print_env_var_error(argv[i]));
		add_env_var(env, argv[i]);
	}
	else
		print_sorted_env_vars(*env);
	return (1);
}
