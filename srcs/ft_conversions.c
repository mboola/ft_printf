/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:58:29 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:58:30 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_err(char c, int *err)
{
	if (write(1, &c, 1) < 0)
		*err = -1;
}

void	ft_putstr_err(char *str, int *err)
{
	while (*str != '\0' && !*err)
	{
		ft_putchar_err(*str, err);
		str++;
	}
}

void	choose_conversion(char const *str, int *err, va_list va)
{
	if (*str == 'c')
		ft_putchar_err(va_arg(va, int), err);
	else if (*str == 's')
		ft_putstr_err(va_arg(va, char *), err);
	//else if (*str == 'p')
	//	ft_putptr_err();
	else if (*str == 'u')
		ft_unsputnbr_base_err(va_arg(va, int), DECBASE, err, 10);
	else if (*str == 'i' || *str == 'd')
		ft_putnbr_base_err(va_arg(va, int), DECBASE, err, 10);
	else if (*str == 'x')
		ft_unsputnbr_base_err(va_arg(va, int), HEXBASELOW, err, 16);
	else if (*str == 'X')
		ft_unsputnbr_base_err(va_arg(va, int), HEXBASEHIG, err, 16);
	else if (*str == '%')
		ft_putchar_err('%', err);
	else
		*err = -1;
}