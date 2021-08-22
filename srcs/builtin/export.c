#include "minishell.h"

int	print_env_var_error(char *arg)
{
	ft_putstr_fd("export: not a valid identifier: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	is_valid_env_var(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	add_env_var(t_env *env, char *arg)
{
	t_env	*new;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->content = ft_strdup(arg);
	new->next = NULL;
	while (env && env->next)
		env = env->next;
	env->next = new;
	return (1);
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
	ft_lstclear(head);
}

/*
** If argument is provided, sets environment variable.
** If not, prints out every environment variable sorted by alphabetical order.
**
** @param	int	argc		The argument count;
** @param	char **argv		The argument vector;
** @param	t_env *env		the head of the environment variables linked list;
** @return	int				1 for success and 0 for failure.
*/
int	ft_export(int argc, char **argv, t_env *env)
{
	int i;

	i = 1;
	if (argv[i])
	{
		if (!is_valid_env_var(argv[i]))
			return (print_env_var_error(argv[i]));
		add_env(env, argv[i]);
	}
	else
		print_sorted_env_vars(env);
	return (1);
}
