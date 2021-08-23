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

void	ft_exit(int argc, char **argv, t_mini *mini);

int		ft_export(int argc, char **argv, t_mini *mini);

int		ft_pwd(void);

int		ft_unset(int argc, char **argv, t_mini *mini);

/*
**	EXE UTILS
*/
int		launch_exe(char *path, char **argv, t_mini *mini);

int		print_exe_path_err(char *path);

/*
**	ENV UTILS
*/
int		add_env_var(t_mini *mini, char *arg);

int		remove_env_var(t_mini *mini, char *arg);

int		set_env_var(t_mini *mini, char *var);

char	*get_env_var(t_mini *, char *var_name);

int		get_env_var_name_size(char *arg);

char	**get_env_arr(t_mini *mini);

int		is_in_env(t_mini *mini, char *arg);

int		is_valid_env_var(char *var);

t_env	*get_sorted_env_vars(t_mini *mini);

// MISC. UTILS

void	free_arr(char **arr);


#endif
