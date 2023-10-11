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

static void	ft_putchar_err(char c, int *len, int *err)
{
	if (write(1, &c, 1) < 0)
		*err = -1;
	else
		*len = *len + 1;
}

static void	ft_putstr_err(char	*str, int *len, int *err)
{
	if (str == NULL)
		*err = -1;
	else
	{
		while (*err != -1 && *str != '\0')
		{
			ft_putchar_err(*str, len, err);
			str++;
		}
	}
}

char	*print_and_reset(char **str, int *len, int *err, int reset)
{
	char	*msg;

	ft_putstr_err(*str, len, err);
	if (*str != NULL)
	{
		free(*str);
		str = NULL;
	}
	if (*err != -1 && reset)
	{
		msg = malloc(sizeof(char));
		if (msg == NULL)
			*err = -1;
		else
			*msg = '\0';
		return (msg);
	}
	return (NULL);
}

char	*print_output(char **output, int *len, int *err, char *conv)
{
	if (*output == NULL)
	{
		*err = -1;
		return (NULL);
	}
	if (**output == '\0' && *conv == 'c')
		ft_putchar_err(**output, len, err);
	return (print_and_reset(output, len, err, 1));
}
