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

char	*create_output(t_percent *opt, va_list va, int *err)
{
	if (opt->conv == '%')
		return (char_to_str('%', err));
	else if (opt->conv == 'c')
		return (create_output_char((char)va_arg(va, int), opt, err));
	else if (opt->conv == 's')
		return (create_output_string(va_arg(va, char *), opt, err));
	else if (opt->conv == 'p')
		return (create_output_pointer(va_arg(va, void *), opt, err));
	else if (opt->conv == 'i' || opt->conv == 'd')
		return (create_output_int(va_arg(va, int), opt, err));
	else if (opt->conv == 'u')
		return (create_output_unsint(va_arg(va, unsigned int), opt, err));
	else if (opt->conv == 'x' || opt->conv == 'X')
		return (create_output_hexa(va_arg(va, unsigned int), opt, err));
	else
		*err = -1;
	return (NULL);
}
<<<<<<< HEAD
=======

static char	*resize_str(char *str, size_t len, int *err)
{
	char	*output;

	output = ft_substr(str, 0, len);
	if (output == NULL)
		*err = -1;
	return (output);
}

static char	*add_plus(char **output, int *err)
{
	char	*tmp;

	if (**output != '-')
	{
		tmp = copy_char('+', err);
		if (*err == -1)
		{
			free(*output);
			return (NULL);
		}
		*output = join_and_free(&tmp, output, err);
	}
	return (*output);
}

char	*create_output(t_percent *options, int *err, va_list va)
{
	char	*output;
	char	*tmp;

	output = convert_value(options->conv, err, va);
	if (*err == -1)
		return (NULL);
	if (options->conv == '%')
		return (output);
	if (options->flag == '+' && (options->conv == 'd' || options->conv == 'i'))
	{
		output = add_plus(&output, err);
		if (*err == -1)
			return (NULL);
	}
	if (options->flag == '0' && options->conv != 'c')
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
>>>>>>> ca1fe68f4f8db8e02dab1cf16155efaed7a017c8
