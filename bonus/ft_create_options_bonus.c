/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_options_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:27:34 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:27:35 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	get_info_conv(t_percent *opt, char *str, int *err)
{
	int		count;

	count = 0;
	opt->info = NULL;
	while (*(str + count) != '\0' && !is_conversion(*(str + count)))
		count++;
	if (*(str + count) == '\0')
	{
		*err = -1;
		return (0);
	}
	opt->conv = *(str + count);
	opt->info = ft_substr(str, 0, count + 1);
	if (opt->info == NULL)
	{
		*err = -1;
		return (0);
	}
	opt->sp_inv = 0;
	opt->add_plus = 0;
	opt->front_space = 0;
	opt->zero = 0;
	opt->base = 0;
	opt->num_spaces = 0;
	opt->num_zeros = 0;
	opt->is_null = 0;
	return (1);
}

static int	get_precision(t_percent *opt, int *err)
{
	int		count;
	char	*str;

	count = 0;
	str = opt->info;
	while (*str != '\0')
	{
		if (*str == '.')
			count++;
		str++;
	}
	if (count > 1)
	{
		*err = -1;
		return (-1);
	}
	opt->prec = count;
	return (1);
}

static char	*get_flags_sub(char *str, int *err)
{
	char	*substr;
	size_t	count;

	count = 0;
	while (*(str + count) != '\0' && is_flag(*(str + count), 0))
		count++;
	substr = ft_substr(str, 0, count + 1);
	if (substr == NULL)
	{
		*err = -1;
		return (NULL);
	}
	str = str + count;
	while (*str != '\0' && (ft_isdigit(*str) || *str == '.'
			|| is_conversion(*str) || *str == '*'))
		str++;
	if (*str != '\0')
	{
		free(substr);
		*err = -1;
		return (NULL);
	}
	return (substr);
}

static int	get_flags(t_percent *opt, int *err)
{
	char	*flags_sub;

	flags_sub = get_flags_sub(opt->info, err);
	if (*err == -1)
		return (0);
	if (ft_strchr(flags_sub, '-') != NULL)
		opt->sp_inv = 1;
	else if (ft_strchr(flags_sub, '0') != NULL)
		opt->zero = 1;
	if (ft_strchr(flags_sub, '+') != NULL && opt->conv != 'x'
		&& opt->conv != 'X')
		opt->add_plus = 1;
	else if (ft_strchr(flags_sub, ' ') != NULL)
		opt->front_space = 1;
	if (ft_strchr(flags_sub, '#') != NULL && (opt->conv == 'x'
			|| opt->conv == 'X'))
		opt->base = 1;
	free(flags_sub);
	return (1);
}

void	create_options(char *str, t_percent *options, va_list va, int *err)
{
	if (!get_info_conv(options, str + 1, err))
		return ;
	if (!get_precision(options, err))
		return ;
	if (!get_flags(options, err))
		return ;
	get_nums(options, va, err);
}
