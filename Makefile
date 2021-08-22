NAME=minishell
GCC=gcc -fsanitize=address -g
SRCS=srcs/*.c srcs/free/*.c srcs/err/*.c srcs/parser/*.c srcs/builtin/*.c srcs/env/*.c srcs/exe/*.c
INC=-I includes
INC_LIBFT=-L libft -lft
OTHER_LIBS=-lreadline

all : ${NAME}

${NAME} :
	make -C libft; make bonus -C libft;
	${GCC} ${INC} ${SRCS} ${INC_LIBFT} ${OTHER_LIBS} -o ${NAME}

clean :
	rm -f *.o
	rm -f libft/*.o

fclean :
	rm -f ${NAME}
	rm -f *.o
	rm -f libft/*.o

re : fclean all

.PHONY : all clean fclean re
