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

static char	*del_t_percent(t_percent *options, char *str)
{
	if (options->info != NULL)
		free(options->info);
	free(options);
	return (str);
}

static char	*convert_and_print(char *str, int *len, va_list va, int *err)
{
	t_percent	*options;
	char		*output;
	int			info_len;

	options = malloc(sizeof(t_percent));
	if (options == NULL)
	{
		*err = -1;
		return (NULL);
	}
	create_options(str, options, va, err);
	if (*err == -1)
		return (del_t_percent(options, str));
	output = create_output(options, va, err);
	if (*err == -1)
		return (del_t_percent(options, str));
	print_and_free_output(&output, len, err);
	if (*err == -1)
		return (del_t_percent(options, str));
	info_len = ft_strlen(options->info);
	del_t_percent(options, str);
	return (str + info_len);
}

static int	print_all_output(char *str, va_list va, int *err)
{
	int		len;

	len = 0;
	while (*err != -1 && *str != '\0')
	{
		if (*str == '%')
			str = convert_and_print(str, &len, va, err);
		else
			ft_putchar_err(*str, err, &len);
		if (*err != -1)
			str++;
	}
	if (*err == -1)
		return (-1);
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
	len = print_all_output(str, va, &err);
	va_end(va);
	if (err)
		return (-1);
	return (len);
}
