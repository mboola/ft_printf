/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:09:39 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:11:04 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef HEXBASELOW
#  define HEXBASELOW "0123456789abcdef"
# endif
# ifndef HEXBASEHIG
#  define HEXBASEHIG "0123456789ABCDEF"
# endif
# ifndef DECBASE
#  define DECBASE "0123456789"
# endif

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(char const *str, ...);

void	choose_conversion(char const *str, int *err, va_list va);

void	ft_putchar_err(char c, int *err);
void	ft_putstr_err(char *str, int *err);
//void	ft_putptr_err(, int *err);

void    ft_unsputnbr_base_err(unsigned int nbr, char *base, int *err, int len);
void	ft_putnbr_base_err(int nbr, char *base, int *err, int len);

#endif
