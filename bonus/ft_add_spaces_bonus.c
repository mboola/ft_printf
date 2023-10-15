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

char	*add_spaces(char **output, t_percent *options, int *err)
{
	char	*spaces;

	spaces = create_str(options->num_spaces - ft_strlen(*output), ' ', err);
	if (*err)
		return (NULL);
	if (*spaces == '\0' && options->front_space && **output != '-')
	{
		free(spaces);
		spaces = char_to_str(' ', err);
		if (*err == -1)
			return (NULL);
		return (join_and_free(&spaces, output, err));
	}
	if (options->sp_inv)
		*output = join_and_free(output, &spaces, err);
	else
		*output = join_and_free(&spaces, output, err);
	return (*output);
}
