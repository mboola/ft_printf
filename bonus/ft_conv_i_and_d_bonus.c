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

static char	*separate_front(char **output, t_percent *opt, int *err)
{
	char	*front;
	char	c;

	if (**output == '-')
	{
		front = ft_strdup(*output + 1);
		free(*output);
		if (front == NULL)
		{
			*err = -1;
			return (NULL);
		}
		*output = front;
		c = '-';
	}
	else if (opt->add_plus)
		c = '+';
	else
		c = '\0';
	front = char_to_str(c, err);
	if (*err == -1)
		free(*output);
	return (front);
}

char	*create_output_int(int n, t_percent *opt, int *err)
{
	char	*output;
	char	*front;

	if (n == 0 && opt->prec && opt->num_zeros == 0)
		return (create_str(opt->num_spaces, ' ', err));
	output = putnbr_sig_err(n, DECBASE, err);
	if (*err == -1)
		return (NULL);
	front = separate_front(&output, opt, err);
	if (*err == -1)
		return (NULL);
	if (opt->prec)
		output = add_zeros(&output, opt, 0, err);
	else if (opt->zero)
	{
		output = add_zeros(&output, opt, (*front != '\0'), err);
		return (join_and_free(&front, &output, err));
	}
	output = join_and_free(&front, &output, err);
	if (*err == -1)
		return (NULL);
	if (opt->num_spaces != 0 || opt->front_space)
		output = add_spaces(&output, opt, err);
	return (output);
}