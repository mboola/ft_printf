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
# include "./libft/libft.h"

int		ft_printf(char const *str, ...);
t_list	*create_node(char c, t_list **lst, int *err);
void	del_node(void *content);
void	ft_putstr_lst(t_list *lst, int *err);
void	choose_conversion(char const *str, t_list **lst, int *err, va_list va);
t_list	*str_to_lst(char *str, int *err);
char	*ft_itoa_base_unsigned(unsigned long n, char *base);
char	*ft_itoa_base_signed(int n, char *base);
t_list	*putnbr_uns_err(unsigned long nbr, char *base, int *err);
t_list	*putnbr_sig_err(int nbr, char *base, int *err);

int	ft_putnbr_base_err(int nbr, char *base, int *err, int len);
int	ft_unsputnbr_base_err(unsigned int nbr, char *base, int *err, int len);
int	ft_longputnbr_base_err(unsigned long nbr, char *base, int *err, int len);

#endif
