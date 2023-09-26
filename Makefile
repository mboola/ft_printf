# VARIABLES

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = libft.a
PRINTF = libftprintf.a

SRCS 			= 	.
HEADER 			= 	${SRCS}/ft_printf.h
FILES			=	${SRCS}/ft_conversions.c ${SRCS}/ft_putnbrbase_err.c ${SRCS}/ft_printf.c
OBJS			=	${FILES:.c=.o}


BONUS_SRCS		=	./bonus
BONUS_HEADER	=	${BONUS_SRCS}/ft_printf_bonus.c
BONUS_FILES 	=	${BONUS_SRCS}/ft_conversions_bonus.c ${BONUS_SRCS}/ft_itoa_base_bonus.c \
					${BONUS_SRCS}/ft_lstaux_bonus.c ${BONUS_SRCS}/ft_printf_bonus.c \
					${BONUS_SRCS}/ft_putnbrbase_err_bonus.c
BONUS_OBJS		=	$(BONUS_FILES:_bonus.c=_bonus.o)

# COMPILE  -L. -lft 
%_bonus.o: %_bonus.c ${BONUS_HEADER} Makefile ${LIBFT}
	${CC} ${CFLAGS} -I ${BONUS_SRCS} -I ${LIBFT_DIR} -c $< -o $@

%.o: %.c ${HEADER} Makefile
	${CC} ${CFLAGS} -I ${SRCS} -c $< -o $@

# RULES

all: ${PRINTF}

${LIBFT}:
	@cd ${LIBFT_DIR} && make
	@cd ${LIBFT_DIR} && mv ${LIBFT} ../

${PRINTF}: ${OBJS}
	@ar rcs $@ ${OBJS}
	@echo "Compilation of $@ succesfull"

clean:
	@cd ${LIBFT_DIR} && make clean
	@rm -f ${OBJS}
	@rm -f ${BONUS_OBJS}

fclean: clean
	@cd ${LIBFT_DIR} && make fclean
	@rm -f ${LIBFT}
	@rm -f ${PRINTF}

re: fclean all

bonus: ${LIBFT} ${BONUS_OBJS}
	@mv ${LIBFT} ${PRINTF}
	@ar rcs ${PRINTF} ${BONUS_OBJS}
	@echo "Compilation of $@ succesfull"
	
.PHONY: all clean fclean re bonus
