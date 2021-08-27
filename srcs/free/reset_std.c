#include "minishell.h"

void	reset_std(t_mini *mini)
{
	dup2(mini->stdin_fd, STDIN_FILENO);
	dup2(mini->stdout_fd, STDOUT_FILENO);
	printf("(reset) stdout is terminal? %d\n", isatty(mini->stdout_fd));
}
