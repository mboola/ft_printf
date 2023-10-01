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

int	is_flag(char c)
{
	if (c == '.' || c == '#' || c == ' ' || c == '+' || c == '-' || c == '0')
		return (1);
	return (0);
}

char	get_flag(char *str, char conv)
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

static int	check_num_correct(char *str, char c, int *ptr, va_list va)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*str == '*' && *(str + 1) != c)
		return (-1);
	else if (*str == '*')
	{
		*ptr = va_arg(va, int);
		return (1);
	}
	while (ft_isdigit(*(str + i)))
		i++;
	if (*(str + i) != c)
		return (-1);
	tmp = ft_substr(str, 0, i);
	if (tmp == NULL)
		return (-1);
	*ptr = ft_atoi(tmp);
	free(tmp);
	return (i);
}

int	check_nums(t_percent *options, va_list va)
{
	char	*str;
	int		i;

	str = options->info;
	if (options->precision && options->flag == '0' && *(str + 1) == '0')
		return (0);
	if (options->flag != -1 && options->flag != '.')
		str++;
	if (options->precision)
	{
		i = check_num_correct(str, '.', &(options->spaces), va);
		if (i == -1)
			return (0);
		str += i + 1;
	}
	else
		options->spaces = 0;
	if (check_num_correct(str, options->conversion, &(options->zeros), va) == -1)
		return (0);
	return (1);
}
