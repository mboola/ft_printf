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
	if (*str == '%')
		return (*str);
	while (*str != '\0' && !is_conversion(*str))
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '%')
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
		else if (conv == 'c')
			return (-1);
	}
	return (count);
}

static char	get_flag(char *str, char conv)
{
	char	flag;

	if (!is_flag(*str) && !ft_isdigit(*str) && *str != conv)
		return (0);
	flag = *str;
	if (flag == '#' && !(conv == 'x' || conv == 'X'))
		return (0);
	if ((flag == '+' || flag == ' ') && !(conv == 'i' || conv == 'd'))
		return (0);
	if (flag == '0' && (conv == 's' || conv == 'c' || conv == 'p'))
		return (0);
	return (*str);
}

/*	Flag might not exist and precision might also not exist
*/
int	check_options_correct(t_percent *options, va_list va)
{
	if (options->info == NULL)
		return (0);
	options->conversion = get_conversion(options->info);
	if (!options->conversion)
		return (0);
	options->precision = get_precision(options->info, options->conversion);
	if (options->precision == -1)
		return (0);
	options->flag = get_flag(options->info, options->conversion);
	if (!options->flag)
		return (0);
	return (check_nums(options, va));
}
