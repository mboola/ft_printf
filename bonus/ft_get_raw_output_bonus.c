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

static char	*copy_str(char *str, int *err)
{
	size_t	count;
	char	*output;

	if (str == NULL)
		return (copy_str("(null)", err));
	count = ft_strlen(str);
	output = malloc(sizeof(char) * (count + 1));
	if (output == NULL)
	{
		*err = -1;
		return (NULL);
	}
	if (ft_strlcpy(output, str, count + 1) == count)
		return (output);
	*err = -1;
	free(output);
	return (NULL);
}

char	*get_raw_output(char conv, va_list va, int *err)
{
	char	*output;

	if (conv == 'c')
		output = char_to_str((char)va_arg(va, int), err);
	else if (conv == 's')
		output = copy_str(va_arg(va, char *), err);
	else if (conv == 'u')
		output = putnbr_uns_err((va_arg(va, unsigned int)), DECBASE, err);
	else if (conv == 'p')
		output = ft_putptr(va_arg(va, void *), HEXBASEL, err);
	else if (conv == 'i' || conv == 'd')
		output = putnbr_sig_err(va_arg(va, int), DECBASE, err);
	else if (conv == 'x')
		output = putnbr_uns_err((va_arg(va, unsigned int)), HEXBASEL, err);
	else if (conv == 'X')
		output = putnbr_uns_err((va_arg(va, unsigned int)), HEXBASEH, err);
	else if (conv == '%')
		output = char_to_str('%', err);
	else
		*err = -1;
	if (*err == -1)
		return (NULL);
	return (output);
}
