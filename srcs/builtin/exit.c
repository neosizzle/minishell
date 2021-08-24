#include "minishell.h"

/*
** Exits the shell
**
** @param	int		argc		The argument count;
** @param	char	**argv		The argument vector;
** @param	t_mini	*mini		The mini struct;
** @return	void				No return value.
*/
void	ft_exit(int argc, char **argv, t_mini *mini)
{
	int	i;

	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	i = 1;
	mini->exit = 1;
	ft_putendl_fd("logout", 2);
	while (argv[i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
		}
		i++;
	}
	if (argv[1])
		mini->exit_status_code = ft_atoi(argv[1]);
	else
		mini->exit_status_code = 0;
}
