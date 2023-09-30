/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_aux_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:27:46 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:27:47 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_putchar_err(char c, int *err)
{
	if (write(1, &c, 1) < 0)
		*err = -1;
}

void	ft_putstr_err(char	*str, int *err)
{
	if (str == NULL)
		*err = 1;
	else
	{
		while (*str != '\0' && !*err)
		{
			ft_putchar_err(*str, err);
			str++;
		}
	}
}
