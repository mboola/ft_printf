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

static char	*create_front(t_percent *opt, int *err, unsigned int n)
{
	char	*front;

	if (opt->base && n != 0)
	{
		if (opt->conv == 'x')
			front = ft_strdup("0x");
		else
			front = ft_strdup("0X");
		if (front == NULL)
			*err = -1;
	}
	else
	{
		front = malloc(sizeof(char));
		if (front == NULL)
			*err = -1;
		else
			*front = '\0';
	}
	return (front);
}

char	*create_output_hexa(unsigned int n, t_percent *opt, int *err)
{
	char	*output;
	char	*front;

	if (n == 0 && opt->prec && opt->num_zeros == 0)
		return (create_str(opt->num_spaces, ' ', err));
	if (opt->conv == 'x')
		output = putnbr_uns_err(n, HEXBASEL, err);
	else
		output = putnbr_uns_err(n, HEXBASEH, err);
	if (*err == -1)
		return (NULL);
	front = create_front(opt, err, n);
	if (opt->prec)
		output = add_zeros(&output, opt, 0, err);
	else if (opt->zero)
	{
		output = add_zeros(&output, opt, 0, err);
		return (join_and_free(&front, &output, err));
	}
	output = join_and_free(&front, &output, err);
	if (*err == -1)
		return (NULL);
	if (opt->num_spaces != 0 || opt->front_space)
		output = add_spaces(&output, opt, err);
	return (output);
}
