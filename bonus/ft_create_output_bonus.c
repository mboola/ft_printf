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


/*

static char	*resize_str(char *str, size_t len, int *err)
{
	char	*output;

	output = ft_substr(str, 0, len);
	if (output == NULL)
		*err = -1;
	return (output);
}

char	*create_output(t_percent *options, int *err, va_list va)
{
	char	*output;
	char	*tmp;

	output = convert_value(options->conv, err, va);
	if (*err)
		return (NULL);
	if (options->conv == '%')
		return (output);
	if (options->flag == '+' && (options->conv == 'd' || options->conv == 'i'))
	{
		if (*output != '-')
		{
			tmp = copy_char('+', err);
			if (*err)
			{
				free(output);
				return (NULL);
			}
			output = join_and_free(&tmp, &output, err);
			if (*err)
				return (NULL);
		}
	}
	if (options->flag == '0')
	{
		tmp = add_zeros(output, options->spaces, options->flag, err);
		free(output);
		output = tmp;
	}
	else
	{
		if (options->zeros != 0 || (options->zeros == 0 && options->prec))
		{
			if (options->prec && options->conv == 's')
				tmp = resize_str(output, options->zeros, err);
			else
				tmp = add_zeros(output, options->zeros, options->flag, err);
			free(output);
			if (*err)
				return (NULL);
			output = tmp;
		}
		if (options->flag == '#' && options->conv == 'x')
			output = add_0x_front(output, err, 0);
		if (options->flag == '#' && options->conv == 'X')
			output = add_0x_front(output, err, 1);
		if (options->spaces != 0 || options->flag == ' ')
		{
			tmp = add_spaces(output, options->spaces, options->flag, err);
			if (*err)
				return (NULL);
			output = tmp;
		}
	}
	return (output);
}
*/

static char	*add_plus(char **output, int *err)
{
	char	*tmp;

	if (**output != '-')
	{
		tmp = char_to_str('+', err);
		if (*err == -1)
		{
			free(*output);
			return (NULL);
		}
		*output = join_and_free(&tmp, output, err);
		if (*err == -1)
			return (NULL);
	}
	return (*output);
}

static char	*add_base(char **output, char conv, int *err)
{
	char	*front;

	if (conv == 'x')
		front = ft_strdup("0x");
	else
		front = ft_strdup("0X");
	if (front == NULL)
	{
		*err = -1;
		free(*output);
		return (NULL);
	}
	return (join_and_free(&front, output, err));
}

char	*create_output(t_percent *options, va_list va, int *err)
{
	char	*output;

	output = get_raw_output(options->conv, va, err);
	if (*err == -1)
		return (NULL);
	if (options->conv == '%')
		return (output);
	if (options->add_plus)
		output = add_plus(&output, err);
	else if (options->base)
		output = add_base(&output, options->conv, err);
	if (*err == -1)
		return (NULL);
	if (options->zero)
		return (add_zeros(&output, options, err));
	if (options->num_zeros != 0 || options->prec)
		output = add_zeros(&output, options, err);
	if (*err == -1)
		return (NULL);
	if (options->num_spaces != 0)
		output = add_spaces(&output, options, err);
	return (output);
}