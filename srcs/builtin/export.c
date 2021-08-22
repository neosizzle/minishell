#include "minishell.h"

int	print_env_var_error(char *arg)
{
	ft_putstr_fd("export: not a valid identifier: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	return (1);
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
	t_env	**head;
	t_env	*sorted_env;

	sorted_env = sort_env(env);
}

int	ft_export(int argc, char **argv, t_env *env)
{
	int i;

	i = 1;
	if (argv[i])
	{
		if (!is_valid_env_var(argv[i]))
			print_env_var_error(argv[i]);
		add_env(env, argv[i]);
	}
	else
	{
		// Print environment variables prefixed with "declared -x" in alphabetical order
		print_sorted_env_vars(env);
		return (1);
	}
}
