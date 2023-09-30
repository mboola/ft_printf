/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:27:34 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:27:35 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
static char	*get_final_output(t_percent *options, int *err, va_list va)
{
	if (!check_options_correct(options))
	{
		*err = 1;
		return (NULL);
	}
	if (options->precision)
		if (check_num_correct(options, '.', va, options->spaces))
		{
			*err = 1;
			return (NULL);
		}
	else
		options->spaces = 0;
	if (check_num_correct(options, options->conversion, va, options->zeros))
	{
		*err = 1;
		return (NULL);
	}
	//info = convert_value(opt, conversion, err, va);
	//if (info == NULL)
	//	return (NULL);
	//if (conversion == flag)
	//	return (info);
	//if flag is a num, add spaces and ends
	//if flag is zero, adds zeros
	info = add_zeros(opt, info, prec, err);
	if (flag == '#')
		info = add_0x_front(info, err);
	else if (flag == ' ')
		//adds one space
	else if (flag = '-')
		//spaces go from behind
	else if (flag == '+')
		//there is always sign
	if (info == NULL)
		return (NULL);
	if (flag = '-')
		//spaces go from behind
	else
		//space go front
	return (info);
}*/

static char	*get_final_output(t_percent *options, int *err, va_list va)
{
	char	*output;

	if (!check_options_correct(options, va))
	{
		*err = 1;
		return (NULL);
	}
	output = create_output(options, err, va);
	if (output == NULL)
		*err = 1;
	return (output);
}

static char	*get_substr_conversion(char *str, int *err)
{
	int		count;
	char	*substr;

	count = 0;
	while (*(str + count) != '\0' && !is_conversion(*(str + count)))
		count++;
	if (*(str + count) == '\0')
	{
		*err = 1;
		return (NULL);
	}
	substr = ft_substr(str, 0, count + 1);
	if (substr == NULL)
		*err = 1;
	return (substr);
}

static char	*del_t_percent(t_percent *options, char *str)
{
	if (options->info != NULL)
		free(options->info);
	free(options);
	return (str);
}

char	*manage_percent(char *str, char **msg, int *err, va_list va)
{
	t_percent	*options;
	char		*output;
	int			len;

	options = malloc(sizeof(t_percent));
	if (options == NULL)
	{
		*err = 1;
		return (str);
	}
	options->info = get_substr_conversion(str, err);
	if (options->info == NULL)
		return (del_t_percent(options, str));
	output = get_final_output(options, err, va);
	if (output == NULL)
		return (del_t_percent(options, str));
	len = ft_strlen(options->info);
	del_t_percent(options, str);
	*msg = join_and_free(*msg, output, err);
	return (str + len);
}
