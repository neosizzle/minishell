#include "minishell.h"

int	ft_exe_env(int argc, char **argv, t_env *env)
{
	char	*var;
	int		status_code;

	var = get_env_var(env, "PATH");
	status_code = launch_exe(var, argv, env);
	return (status_code);
}
