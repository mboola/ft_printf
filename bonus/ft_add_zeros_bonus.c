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

static char	*add_zeros_front(char *output, t_percent *opt, int len, int *err)
{
	char	*substr;
	char	*raw_str;
	size_t	num_chars;
	char	*zeros;

	substr = ft_substr(output, 0, len);
	if (substr == NULL)
	{
		*err = -1;
		return (NULL);
	}
	raw_str = ft_strdup(output + len);
	if (raw_str == NULL)
	{
		free(substr);
		*err = -1;
		return (NULL);
	}
	if (opt->zero)
		num_chars = ft_strlen(output);
	else
		num_chars = ft_strlen(raw_str);
	if (opt->zero)
		zeros = create_str(opt->num_spaces - num_chars, '0', err);
	else
		zeros = create_str(opt->num_zeros - num_chars, '0', err);
	if (*err == -1)
	{
		free(substr);
		free(raw_str);
		return (NULL);
	}
	zeros = join_and_free(&zeros, &raw_str, err);
	if (*err == -1)
	{
		free(substr);
		return (NULL);
	}
	return (join_and_free(&substr, &zeros, err));
}

char	*add_zeros(char **output, t_percent *opt, int *err)
{
	char	*zeros;
	int		len;

	if (opt->base && (opt->conv == 'x' || opt->conv == 'X'))
		len = 2;
	else if (opt->add_plus && (opt->conv == 'd' || opt->conv == 'i'))
		len = 1;
	else if ((opt->conv == 'd' || opt->conv == 'i') && **output == '-')
		len = 1;
	else
		len = 0;
	zeros = add_zeros_front(*output, opt, len, err);
	free(*output);
	return (zeros);
}
