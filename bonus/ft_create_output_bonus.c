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

char	*copy_char(int c, int *err)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	if (str == NULL)
	{
		*err = 1;
		return (NULL);
	}
	*str = (char)c;
	*(str + 1) = '\0';
	return (str);
}

char	*copy_str(char *str, int *err)
{
	size_t	count;
	char	*info;

	if (str == NULL)
		return (copy_str("(null)", err));
	count = ft_strlen(str);
	info = malloc(sizeof(char) * (count + 1));
	if (info == NULL)
	{
		*err = 1;
		return (NULL);
	}
	if (ft_strlcpy(info, str, count + 1) == count)
		return (info);
	*err = 1;
	free(info);
	return (NULL);
}

static char	*convert_value(char conv, int *err, va_list va)
{
	char	*info;

	if (conv == 'c')
		info = copy_char((char)va_arg(va, int), err);
	else if (conv == 's')
		info = copy_str(va_arg(va, char *), err);
	else if (conv == 'u')
		info = putnbr_uns_err((va_arg(va, unsigned int)), DECBASE, err);
	else if (conv == 'p')
		info = ft_putptr(va_arg(va, void *), HEXBASEL, err);
	else if (conv == 'i' || conv == 'd')
		info = putnbr_sig_err(va_arg(va, int), DECBASE, err);
	else if (conv == 'x')
		info = putnbr_uns_err((va_arg(va, unsigned int)), HEXBASEL, err);
	else if (conv == 'X')
		info = putnbr_uns_err((va_arg(va, unsigned int)), HEXBASEH, err);
	else if (conv == '%')
		info = copy_char('%', err);
	else
		*err = 1;
	if (!*err)
		return (info);
	return (NULL);
}

static char	*resize_str(char *str, size_t len, int *err)
{
	char	*output;

	output = ft_substr(str, 0, len);
	if (output == NULL)
		*err = 1;
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
