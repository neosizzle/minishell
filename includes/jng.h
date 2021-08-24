#ifndef JNG_H
# define JNG_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

//Macros
/*
** Token types
**
** Empty : ' '
** cmd_builtin : any type of builtin cmd: e.g. echo, cat etc...
** cmd_builtin : any type of exe file
** arg : any type of argument for a command e.g. asdf, a.txt...
** trunc : '>'
** append : '>>'
** input : '<'
** heredoc : '<<'
** pipe : '|'
** and : '&&'
** or : '||'
*/
# define CMD_BUILTIN 1
# define CMD_EXE 2
# define ARG 3
# define TRUNC 4
# define APPEND 5
# define INPUT 6
# define HEREDOC 7
# define PIPE 8
# define AND 9
# define OR 0

//Structs

/*
** Struct that contains signal data
**
** str - Buffer string
** next - linked list pointers to prev or next buffer in history
*/
typedef struct s_signal
{
	int		sigint;
	char	*prompt;
}	t_signal;


/*
** Struct that contains token data stored in linked list structure
**
** str - Token string
** type - Token type (refer to macros)
** prev and next - linked list pointers to prev or next token
*/
typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/*
** Struct that contains buffer data stored in linked list structure
**
** str - Buffer string
** next - linked list pointers to prev or next buffer in history
*/
typedef struct s_history
{
	char				*str;
	struct s_history	*next;
}	t_history;


/*
** Struct that contains minishell data
**
**
** tokens - head of tokens linked list
** envs - head of env linked list
** history - head of history linked list
** cmd - comamnd exists in current parsing
** exit - exit status
*/
typedef struct s_mini
{
	t_token		*tokens;
	t_env		*envs;
	t_history	*history;
	int			cmd;
	int			exit;
	int			exit_status_code;
}	t_mini;

//Global vars
extern t_signal g_signal;

//Error functions
void	err(char *message);
void	err_noexit(char *message);

//Free functions
void	free_mini(t_mini *mini);
void	free_tokens(t_token *head);
void	free_term(char *cwd, char *buff);
void	free_history(t_history *head);

//Parsing functions
void	parse(t_mini *mini, char *buff);
int		get_type(t_mini *mini, char *token);
char	**ft_split_custom(char *s, char c);
int		bad_quotes(char *buff);
int		bad_bs(char *buff);
void	trim(t_mini *mini);

//Executor functions
int		execute(t_mini *mini);
void	exe_builtin(t_mini *mini, char *cmd, char **args);
void	exe_executable(t_mini *mini, char *cmd, char **args);
int		get_argc(char **args);

//History functions
void	push_history(t_mini *mini, char *buff);
void	print_history(t_mini *mini);

#endif
