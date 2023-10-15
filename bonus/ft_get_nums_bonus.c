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

static int	get_range(int *num, char **str, char delimiter, va_list va)
{
	if (**str == '*' && *(*str + 1) != delimiter)
		return (0);
	else if (**str == '*')
	{
		*num = va_arg(va, int);
		(*str)++;
	}
	else
		*num = ft_atoi(*str);
	while (**str != delimiter && **str != '*')
		(*str)++;
	if (**str == '*')
		return (0);
	return (1);
}

int	get_nums(t_percent *opt, va_list va, int *err)
{
	char	*str;

	str = opt->info;
	while (*str != opt->conv && is_flag(*str, 0))
		str++;
	if (*str == opt->conv)
		return (1);
	if (opt->prec)
	{
		if (!get_range(&(opt->num_spaces), &str, '.', va))
		{
			*err = -1;
			return (0);
		}
		str++;
		if (!get_range(&(opt->num_zeros), &str, opt->conv, va))
		{
			*err = -1;
			return (0);
		}
	}
	else if (!get_range(&(opt->num_spaces), &str, opt->conv, va))
	{
		*err = -1;
		return (0);
	}
	return (1);
}
