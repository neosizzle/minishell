#include "minishell.h"

int	ft_exe_path(int argc, char **argv, t_env *env)
{
	int		status_code;

	status_code = launch_exe(argv[0], argv, env);
	return (status_code);
}
