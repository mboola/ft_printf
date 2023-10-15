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

char	*create_output_char(char **output, t_percent *opt, int *len, int *err)
{
	char	*spaces;

	if (**output == '\0')
		*len += 1;
	spaces = create_str(opt->num_spaces - 1, ' ', err);
	if (*err == -1)
		return (NULL);
	if (opt->sp_inv)
		*output = join_and_free(output, &spaces, err);
	else
		*output = join_and_free(&spaces, output, err);
	if (*err == -1)
		return (NULL);
	return (*output);
}