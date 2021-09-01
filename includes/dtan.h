#ifndef DTAN_H
# define DTAN_H

# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include "jng.h"

/*
**	BUILT-IN
*/
int		ft_cd(int argc, char **argv, t_mini *mini);
int		ft_echo(int argc, char **argv);
int		ft_env(t_mini *mini);
int		ft_exit(int argc, char **argv, t_mini *mini);
int		ft_export(int argc, char **argv, t_mini *mini);
int		ft_pwd(void);
int		ft_unset(int argc, char **argv, t_mini *mini);

/*
**	BUILT-IN UTILS
*/
char	*get_env_path(t_env *env, char *var);
int		print_cd_error(char *arg);

/*
**	EXE UTILS
*/
int		launch_exe(char *path, char **argv, t_mini *mini);
int		get_err_status_code(char *path);
int		ft_exe_path(int argc, char **argv, t_mini *mini);
int		ft_exe_env(int argc, char **argv, t_mini *mini);

/*
**	ENV UTILS
*/
int		add_env_var(t_mini *mini, char *arg);
int		remove_env_var(t_mini *mini, char *arg);
int		set_env_var(t_mini *mini, char *var);
char	*get_env_var(t_mini *mini, char *var_name);
int		get_env_var_name_size(char *arg);
char	**get_env_arr(t_mini *mini);
int		is_in_env(t_mini *mini, char *arg);
int		is_valid_env_var(char *var);
t_env	*get_sorted_env_vars(t_mini *mini);
void	add_env_back(t_mini *mini, t_env *env);

/*
**	PIPE UTILS
*/
int		create_pipe(t_mini *mini);

/*
**	REDIRECTION UTILS
*/
int		redir_input(t_mini *mini, t_token *token);
int		redir_output(t_mini *mini, t_token *token, int type);

// MISC. UTILS

void	free_arr(char **arr);
void	reset_std(t_mini *mini);
void	close_fds(t_mini *mini);

#endif
