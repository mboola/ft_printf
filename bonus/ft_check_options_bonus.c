/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:28:22 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:28:23 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	is_conversion(char c)
{
	if (c == 'c' || c == 's' || c == 'u' || c == 'p' || c == 'i' || c == 'd'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

static char	get_conversion(char *str)
{
	while (*str != '\0' && !is_conversion(*str))
		str++;
	if (*str == '\0')
		return (0);
	return (*str);
}

static int	get_precision(char *str, char conv)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '.')
			count++;
		str++;
	}
	if (count > 1)
		return (-1);
	if (count)
	{
		if (conv == 'p')
			return (-1);
	}
	return (count);
}

int	check_options(t_percent *options, va_list va)
{
	if (options->info == NULL)
		return (0);
	options->conv = get_conversion(options->info);
	if (!options->conv)
		return (0);
	options->prec = get_precision(options->info, options->conv);
	if (options->prec == -1)
		return (0);
	options->flag = get_flag(options->info, options->conv, options->prec);
	if (!options->flag)
		return (0);
	return (check_nums(options, va));
}
