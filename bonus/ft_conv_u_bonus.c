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

char	*create_output_unsint(unsigned int n, t_percent *opt, int *err)
{
	char	*output;

	if (n == 0 && opt->prec && opt->num_zeros == 0)
		return (create_str(opt->num_spaces, ' ', err));
	output = putnbr_uns_err(n, DECBASE, err);
	if (opt->prec)
		output = add_zeros(&output, opt, 0, err);
	else if (opt->zero)
		return (add_zeros(&output, opt, 0, err));
	if (*err == -1)
		return (NULL);
	if (opt->num_spaces != 0 || opt->front_space)
		output = add_spaces(&output, opt, err);
	return (output);
}