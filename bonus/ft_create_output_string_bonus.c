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

static char	*resize_str(char *str, size_t len, int *err)
{
	char	*output;

	output = ft_substr(str, 0, len);
	if (output == NULL)
		*err = -1;
	return (output);
}

char	*create_output_string(char **output, t_percent *opt, int *err)
{
	char	*zeros;
	char	*spaces;

	if (opt->prec)
	{
		zeros = resize_str(*output, opt->num_zeros, err);
		free(*output);
		if (*err == -1)
			return (NULL);
		*output = zeros;
	}
	spaces = create_str(opt->num_spaces - ft_strlen(*output), ' ', err);
	if (*err == -1)
	{
		free(*output);
		return (NULL);
	}
	if (opt->sp_inv)
		*output = join_and_free(output, &spaces, err);
	else
		*output = join_and_free(&spaces, output, err);
	return (*output);
}