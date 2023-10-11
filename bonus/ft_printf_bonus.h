/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:28:59 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:28:59 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# ifndef HEXBASEL
#  define HEXBASEL "0123456789abcdef"
# endif
# ifndef HEXBASEH
#  define HEXBASEH "0123456789ABCDEF"
# endif
# ifndef DECBASE
#  define DECBASE "0123456789"
# endif

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct t_percent
{
	char	*info;
	char	flag;
	char	conv;
	int		prec;
	size_t	spaces;
	size_t	zeros;
}	t_percent;

int		ft_printf(char const *str, ...);
char	*join_and_free(char **s1, char **s2, int *err);
char	*print_and_reset(char **msg, int *len, int *err, int reset);
char	*convert_to_output(char *str, char **msg, int *err, va_list va);
char	*print_output(char **output, int *len, int *err, char *conv);
int		check_options(t_percent *options, va_list va);

int		check_nums(t_percent *options, va_list va);
char	get_flag(char *str, char conv, int prec);
int		is_conversion(char c);
char	*create_output(t_percent *options, int *err, va_list va);
char	*add_0x_front(char *str, int *err, int upper);
char	*ft_putptr(void *ptr, char *base, int *err);
char	*putnbr_sig_err(int nbr, char *base, int *err);
char	*putnbr_uns_err(unsigned int nbr, char *base, int *err);
char	*copy_str(char *str, int *err);
char	*copy_char(int c, int *err);
char	*add_zeros(char *output, size_t zeros_len, char flag, int *err);
char	*add_spaces(char *output, size_t spaces_len, char flag, int *err);

#endif
