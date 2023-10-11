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

static char	*create_str(size_t outp_len, size_t total_len, char c, int *err)
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

char	*add_zeros(char *output, size_t zeros_len, char flag, int *err)
{
	char	*zeros;
	char	*tmp;
	int		neg;

	if (*output == '-')
		neg = 1;
	else
		neg = 0;
	if (neg || flag == '+')
		tmp = copy_str(output + 1, err);
	else
		tmp = copy_str(output, err);
	if (*err)
		return (NULL);
	if (zeros_len > 0)
		zeros_len = zeros_len + (flag == '0') * (neg == 1) * -1;
	zeros = create_str(ft_strlen(tmp), zeros_len, '0', err);
	if (*err)
	{
		free(tmp);
		return (NULL);
	}
	if (*zeros == '\0')
	{
		free(zeros);
		free(tmp);
		return (copy_str(output, err));
	}
	tmp = join_and_free(&zeros, &tmp, err);
	if (*err)
		return (NULL);
	if (flag == '+' || neg)
	{
		if (neg)
			zeros = copy_char('-', err);
		else
			zeros = copy_char('+', err);
		if (*err)
		{
			free(tmp);
			return (NULL);
		}
		return (join_and_free(&zeros, &tmp, err));
	}
	return (tmp);
}

char	*add_spaces(char *output, size_t spaces_len, char flag, int *err)
{
	char	*spaces;

	spaces = create_str(ft_strlen(output), spaces_len, ' ', err);
	if (*err)
		return (NULL);
	if (*spaces == '\0' && flag == ' ' && *output != '-')
	{
		free(spaces);
		spaces = copy_char(' ', err);
		return (join_and_free(&spaces, &output, err));
	}
	if (flag == '-')
		output = join_and_free(&output, &spaces, err);
	else
		output = join_and_free(&spaces, &output, err);
	return (output);
}
