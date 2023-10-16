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
	char	conv;
	char	prec;
	char	sp_inv;
	char	add_plus;
	char	front_space;
	char	zero;
	char	base;
	int		num_spaces;
	int		num_zeros;
}	t_percent;

int		ft_printf(char const *str, ...);
void	create_options(char *str, t_percent *options, va_list va, int *err);
char	*create_output(t_percent *options, va_list va, int *len, int *err);
char	*create_output_char(char c, t_percent *opt, int *len, int *err);
char	*create_output_string(char *output, t_percent *opt, int *err);
char	*create_output_pointer(void *ptr, t_percent *opt, int *err);
void	print_and_free_output(char **output, int *len, int *err);
int		get_nums(t_percent *opt, va_list va, int *err);
char	*get_raw_output(char conv, va_list va, int *err);
char	*add_zeros(char **output, t_percent *opt, int *err);
char	*add_spaces(char **output, t_percent *options, int *err);
char	*putnbr_sig_err(int nbr, char *base, int *err);
char	*putnbr_uns_err(unsigned int nbr, char *base, int *err);
int		is_flag(char c, int prec);
int		is_conversion(char c);
char	*char_to_str(char c, int *err);
char	*copy_str(char *str, int *err);
char	*create_str(int length, char c, int *err);
char	*join_and_free(char **s1, char **s2, int *err);
void	ft_putchar_err(char c, int *len, int *err);

#endif
