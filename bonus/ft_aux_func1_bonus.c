/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_func1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:27:34 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:27:35 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	is_flag(char c, int prec)
{
	if (c == '#' || c == ' ' || c == '+' || c == '-' || c == '0')
		return (1);
	if (prec && c == '.')
		return (1);
	return (0);
}

int	is_conversion(char c)
{
	if (c == 'c' || c == 's' || c == 'u' || c == 'p' || c == 'i' || c == 'd'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

char	*create_str(int length, char c, int *err)
{
	char	*tmp;
	size_t	len;

	if (length < 0)
		len = 0;
	else
		len = length;
	tmp = malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
	{
		*err = 1;
		return (NULL);
	}
	ft_memset(tmp, c, len);
	*(tmp + len) = '\0';
	return (tmp);
}

char	*copy_str(char *str, int *err)
{
	size_t	count;
	char	*output;

	if (str == NULL)
		return (copy_str("(null)", err));
	count = ft_strlen(str);
	output = malloc(sizeof(char) * (count + 1));
	if (output == NULL)
	{
		*err = -1;
		return (NULL);
	}
	if (ft_strlcpy(output, str, count + 1) == count)
		return (output);
	*err = -1;
	free(output);
	return (NULL);
}

char	*join_and_free(char **s1, char **s2, int *err)
{
	char	*tmp;

	tmp = ft_strjoin(*s1, *s2);
	if (tmp == NULL)
		*err = -1;
	if (*s1 != NULL)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (*s2 != NULL)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (tmp);
}
