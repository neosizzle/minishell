#ifndef DTAN_H
# define DTAN_H

# include <unistd.h>

typedef struct s_env {
	char			*content;
	struct s_env	*next;
}				t_env;

#endif
