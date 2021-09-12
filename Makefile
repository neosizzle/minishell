NAME=minishell
GCC=gcc -Wall -Wextra -Werror -g -fsanitize=address
SRCS=srcs/*.c srcs/free/*.c srcs/err/*.c srcs/parser/*.c srcs/builtin/*.c \
	srcs/env/*.c srcs/exe/*.c srcs/executor/*.c srcs/history/*.c srcs/signals/*.c \
	srcs/pipe/*.c srcs/redirect/*.c
INC=-I includes
#INC_LIBFT=-L libft -lft
INC_LIBFT=libft/*.c
OTHER_LIBS=-lreadline

all : ${NAME}

${NAME} :
	make -C libft; make bonus -C libft;
	${GCC} ${INC} ${SRCS} ${INC_LIBFT} -o ${NAME} ${OTHER_LIBS}

nolibft :
	${GCC} ${INC} ${SRCS} ${INC_LIBFT} -o ${NAME} ${OTHER_LIBS}

clean :
	rm -f *.o
	rm -f libft/*.o

fclean :
	rm -f ${NAME}
	rm -f *.o
	rm -f libft/*.o

re : fclean all

.PHONY : all clean fclean re
