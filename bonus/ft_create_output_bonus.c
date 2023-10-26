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
		return (create_output_char('%', opt, err));
	if (opt->conv == 'c' || opt->conv == '%')
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
