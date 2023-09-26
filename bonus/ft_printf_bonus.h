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

int		ft_printf(char const *str, ...);
t_list	*str_to_lst(char *str, int *err);
void	del_node(void *content);
t_list	*create_lst(char c, t_list **lst, int *err);
void	print_lst(t_list *lst, int *err);
t_list	*ft_putptr(void *ptr, char *base, int *err);
void	choose_conversion(char const *str, t_list **lst, int *err, va_list va);
t_list	*putnbr_uns_err(unsigned int nbr, char *base, int *err);
t_list	*putnbr_sig_err(int nbr, char *base, int *err);
char	*ft_itoa_base(unsigned int n, char *base, char *str, int size);
char	*ft_itoa_base_long(unsigned long n, char *base, int *err);

#endif
