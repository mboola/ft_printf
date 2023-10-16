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

char	*char_to_str(char c, int *err)
{
	char	*str;

	if (c == '\0')
		str = malloc(sizeof(char));
	else
		str = malloc(sizeof(char) + 1);
	if (str == NULL)
	{
		*err = -1;
		return (NULL);
	}
	*str = c;
	if (c != '\0')
		*(str + 1) = '\0';
	return (str);
}

char	*create_output_char(char c, t_percent *opt, int *len, int *err)
{
	char	*output;
	char	*spaces;

	if (c == '\0')
		*len += 1;
	output = char_to_str(c, err);
	if (*err == -1)
		return (NULL);
	spaces = create_str(opt->num_spaces - 1, ' ', err);
	if (*err == -1)
	{
		free(output);
		return (NULL);
	}
	if (opt->sp_inv)
		output = join_and_free(&output, &spaces, err);
	else
		output = join_and_free(&spaces, &output, err);
	return (output);
}
