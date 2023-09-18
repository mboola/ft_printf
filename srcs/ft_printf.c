/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:20:50 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *str, ...)
{
	int	err;
	va_list va;

	err = 0;
	va_start(va, str);
	while (*str != '\0' && !err)
	{
		if (*str == '%')
		{
			str++;
			choose_conversion(str, &err, va);
		}
		else
			ft_putchar_err(*str, &err);
		str++;
	}
	va_end(va);
	if (err)
		return (0);
	return (1);
}
