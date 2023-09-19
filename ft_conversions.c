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

int	ft_putchar_err(char c, int *err)
{
	if (write(1, &c, 1) < 0)
		*err = -1;
	return (1);
}

int	ft_putstr_err(char *str, int *err)
{
	int	count;

	count = 0;
	while (*str != '\0' && !*err)
	{
		ft_putchar_err(*str, err);
		str++;
		count++;
	}
	return (count);
}

int	choose_conversion(char const *str, int *err, va_list va)
{
	int	count;

	count = 0;
	if (*str == 'c')
		count = ft_putchar_err(va_arg(va, int), err);
	else if (*str == 's')
		count = ft_putstr_err(va_arg(va, char *), err);
	else if (*str == 'u')
		count = ft_unsputnbr_base_err(va_arg(va, int), DECBASE, err, 10);
	else if (*str == 'i' || *str == 'd')
		count = ft_putnbr_base_err(va_arg(va, int), DECBASE, err, 10);
	else if (*str == 'x')
		count = ft_unsputnbr_base_err(va_arg(va, int), HEXBASELOW, err, 16);
	else if (*str == 'X')
		count = ft_unsputnbr_base_err(va_arg(va, int), HEXBASEHIG, err, 16);
	else if (*str == '%')
		count = ft_putchar_err('%', err);
	else
		*err = -1;
	return (count);
}
