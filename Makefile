# VARIABLES
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = libft.a

PRINTF = libftprintf.a

HEADER_PRINTF = ft_printf.h
INCLUDES_PRINTF = .

SRCS = .
FILES = ${SRCS}/ft_conversions.c ${SRCS}/ft_putnbrbase_err.c ${SRCS}/ft_printf.c \
		${SRCS}/ft_lstaux.c ${SRCS}/ft_itoa_base.c

OBJS = ${FILES:.c=.o}

# COMPILE

%.o: %.c ${HEADER} Makefile ${LIBFT}
	${CC} ${CFLAGS} -I ${LIBFT_DIR} -I ${INCLUDES_PRINTF} -c $< -o $@ -L. -lft 

# RULES

all: ${PRINTF}

${LIBFT}:
	@cd ${LIBFT_DIR} && make
	@cd ${LIBFT_DIR} && mv ${LIBFT} ../
	@mv ${LIBFT} ${PRINTF}

${PRINTF}: ${LIBFT} ${OBJS}
	@ar rcs $@ ${OBJS}
	@echo "Compilation of $@ succesfull"

clean:
	@cd ${LIBFT_DIR} && make clean
	@rm -f ${OBJS}

fclean: clean
	@cd ${LIBFT_DIR} && make fclean
	@rm -f ${LIBFT}
	@rm -f ${PRINT}

re: fclean all

.PHONY: all clean fclean re
