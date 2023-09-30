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

char	*join_and_free(char *s1, char *s2, int *err)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (tmp == NULL)
		*err = 1;
	free(s1);
	free(s2);
	return (tmp);
}

static char	*create_msg(char *str, va_list va, int *err)
{
	char	*msg;
	char	*c;

	msg = malloc(sizeof(char));
	if (msg == NULL)
	{
		*err = 1;
		return (NULL);
	}
	*msg = '\0';
	while (*str != '\0' && !*err)
	{
		if (*str == '%')
		{
			str++;
			str = manage_percent(str, &msg, err, va);
		}
		else
		{
			c = ft_substr(str, 0, 1);
			if (c == NULL)
			{
				*err = 1;
				free(msg);
				return (NULL);
			}
			msg = join_and_free(msg, c, err);
			if (msg == NULL)
				return (NULL);
			str++;
		}
	}
	if (*err)
	{
		free(msg);
		msg = NULL;
	}
	return (msg);
}

int	ft_printf(char const *s, ...)
{
	int		err;
	va_list	va;
	char	*msg;
	char	*str;

	str = (char *)s;
	if (s == NULL)
		return (-1);
	err = 0;
	va_start(va, s);
	msg = create_msg(str, va, &err);
	va_end(va);
	if (err)
		return (-1);
	ft_putstr_err(msg, &err);
	if (err)
	{
		free(msg);
		return (-1);
	}
	err = ft_strlen(msg);
	free(msg);
	return (err);
}
