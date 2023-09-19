# VARIABLES
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

INCLUDES = .
HEADER = ${INCLUDES}/ft_printf.h

SRCS = .
FILES = ${SRCS}/ft_conversions.c ${SRCS}/ft_putnbrbase_err.c ${SRCS}/ft_printf.c 

OBJS = ${FILES:.c=.o}

# COMPILE

%.o: %.c ${HEADER} Makefile
	${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

# RULES

all: ${NAME}

${NAME}: ${OBJS}
	ar -rc $@ ${OBJS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
