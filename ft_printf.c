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
	int		err;
	int		count;
	va_list	va;

	if (str == NULL)
		return (-1);
	err = 0;
	count = 0;
	va_start(va, str);
	while (*str != '\0' && !err)
	{
		if (*str == '%')
		{
			str++;
			count += choose_conversion(str, &err, va);
		}
		else
			count += ft_putchar_err(*str, &err);
		str++;
	}
	va_end(va);
	if (err)
		return (-1);
	return (count);
}
