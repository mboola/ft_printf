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

static char	*create_str_of_char(size_t outp_len, size_t total_len, char c, int *err)
{
	char	*str;
	size_t	len;

	if (outp_len >= total_len)
	{
		str = malloc(sizeof(char));
		if (str == NULL)
		{
			*err = 1;
			return (NULL);
		}
		*str = '\0';
		return (str);
	}
	len = total_len - outp_len;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
	{
		*err = 1;
		return (NULL);
	}
	ft_memset(str, c, len);
	*(str + len) = '\0';
	return (str);
}

char	*add_zeros(char *output, t_percent *options, int *err)
{
	char	*zeros;
	char	*tmp;
	int		neg;

	zeros = create_str_of_char(ft_strlen(output), options->zeros, '0', err);
	if (!*err && *zeros == '\0')
		return (zeros);
	if (*err)
		return (NULL);
	if (*output == '-')
		neg = 1;
	else
		neg = 0;
	tmp = copy_str(output + neg, err);
	if (*err)
		return (NULL);
	tmp = join_and_free(zeros, tmp, err);
	if (tmp == NULL)
		return (NULL);
	if (!neg)
		return (tmp);
	zeros = copy_char('-', err);
	if (zeros == NULL)
	{
		free(tmp);
		return (NULL);
	}
	tmp = join_and_free(zeros, tmp, err);
	return (tmp);
}

char	*add_spaces(char *output, t_percent *options, int *err)
{
	char	*spaces;

	spaces = create_str_of_char(ft_strlen(output), options->spaces, ' ', err);
	if (*err)
		return (NULL);
	if (options->flag == '-')
		output = join_and_free(output, spaces, err);
	else
		output = join_and_free(spaces, output, err);
	return (output);
}