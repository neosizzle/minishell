#ifndef JNG_H
#define JNG_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

//Macros
/*
** Token types
** 
** Empty : ' '
** cmd : any type of cmd: e.g. echo, cat etc...
** arg : any type of argument for a command e.g. asdf, a.txt...
** trunc : '>'
** append : '>>'
** input : '<'
** heredoc : '<<'
*/
# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define HEREDOC 6
# define PIPE 7
# define AND 8
# define OR 9

//Structs
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
** Struct that contains env data stored in linked list structure
** 
** str - env string
** next - ponints to the next env
*/
typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;


/*
** Struct that contains minishell data
** 
** 
** tokens - head of tokens linked list
** envs - head of env linked list
** cmd - comamnd exists in current parsing
** exit - exit status
*/
typedef struct s_mini
{
	t_token	*tokens;
	t_env	*envs;
	int		cmd;
	int		exit;
}	t_mini;

//Error functions
void	err(char *message);

//Free functions
void	free_mini(t_mini *mini);
void	free_term(char *cwd, char *buff);

//Parsing functions
void	parse(t_mini *mini, char *buff);
int		get_type(t_mini *mini, char *token);

#endif