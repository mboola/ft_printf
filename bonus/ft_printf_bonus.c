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

char	*join_and_free(char **s1, char **s2, int *err)
{
	char	*tmp;

	tmp = ft_strjoin(*s1, *s2);
	if (tmp == NULL)
		*err = -1;
	free(*s1);
	*s1 = NULL;
	free(*s2);
	*s2 = NULL;
	return (tmp);
}

static int	create_msg(char *str, va_list va, int *err)
{
	char	*msg;
	char	*str_c;
	int		len;

	msg = malloc(sizeof(char));
	if (msg == NULL)
		*err = -1;
	else
		*msg = '\0';
	len = 0;
	while (*err != -1 && *str != '\0')
	{
		if (*str == '%')
		{
			msg = print_and_reset(&msg, &len, err, 1);
			if (*err != -1)
			{
				str = convert_output(str, &msg, err, va);
				msg = print_output(&msg, &len, err, str);
			}
		}
		else
		{
			str_c = ft_substr(str, 0, 1);
			if (str_c == NULL)
				*err = -1;
			else
				msg = join_and_free(&msg, &str_c, err);
		}
		if (*err != -1)
			str++;
	}
	if (*err == -1 && msg != NULL)
		free(msg);
	print_and_reset(&msg, &len, err, 0);
	return (len);
}

int	ft_printf(char const *s, ...)
{
	int		err;
	va_list	va;
	int		len;
	char	*str;

	str = (char *)s;
	if (s == NULL)
		return (-1);
	err = 0;
	va_start(va, s);
	len = create_msg(str, va, &err);
	va_end(va);
	if (err)
		return (-1);
	return (len);
}
