/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:27:34 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:27:35 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*get_output(t_percent *options, int *err, va_list va)
{
	char	*output;

	if (!check_options(options, va))
	{
		*err = -1;
		return (NULL);
	}
	output = create_output(options, err, va);
	return (output);
}

static char	*create_substr_conversion(char *str, int *err)
{
	int		count;
	char	*substr;

	count = 0;
	while (*(str + count) != '\0' && !is_conversion(*(str + count)))
		count++;
	if (*(str + count) == '\0')
	{
		*err = -1;
		return (NULL);
	}
	substr = ft_substr(str, 0, count + 1);
	if (substr == NULL)
		*err = -1;
	return (substr);
}

static char	*del_t_percent(t_percent *options, char *str)
{
	if (options->info != NULL)
		free(options->info);
	free(options);
	return (str);
}

char	*convert_to_output(char *str, char **msg, int *err, va_list va)
{
	t_percent	*options;
	char		*output;
	int			len;

	options = malloc(sizeof(t_percent));
	if (options == NULL)
	{
		*err = -1;
		return (str);
	}
	options->info = create_substr_conversion(str + 1, err);
	if (*err == -1)
		return (del_t_percent(options, str));
	output = get_output(options, err, va);
	if (*err == -1)
		return (del_t_percent(options, str));
	len = ft_strlen(options->info);
	del_t_percent(options, str);
	*msg = join_and_free(msg, &output, err);
	return (str + len);
}
