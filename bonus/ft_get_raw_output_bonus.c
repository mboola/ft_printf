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

char	*get_raw_output(char conv, va_list va, int *err)
{
	char	*output;

	if (conv == 'u')
		output = putnbr_uns_err((va_arg(va, unsigned int)), DECBASE, err);
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
