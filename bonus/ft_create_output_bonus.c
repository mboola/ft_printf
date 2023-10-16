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

char	*create_output(t_percent *opt, va_list va, int *len, int *err)
{
	char	*output;

	if (opt->conv == '%')
		return (char_to_str('%', err));
	else if (opt->conv == 'c')
		return (create_output_char((char)va_arg(va, int), opt, len, err));
	else if (opt->conv == 's')
		return (create_output_string(va_arg(va, char *), opt, err));
	else if (opt->conv == 'p')
		return (create_output_pointer(va_arg(va, void *), opt, err));

	output = get_raw_output(opt->conv, va, err);
	if (*err == -1)
		return (NULL);
	if (opt->add_plus)
		output = add_plus(&output, err);
	else if (opt->base)
		output = add_base(&output, opt->conv, err);
	if (*err == -1)
		return (NULL);
	if (opt->zero)
		return (add_zeros(&output, opt, err));
	if (opt->prec)
		output = add_zeros(&output, opt, err);
	if (*err == -1)
		return (NULL);
	if (opt->num_spaces != 0 || opt->front_space)
		output = add_spaces(&output, opt, err);
	return (output);
}
